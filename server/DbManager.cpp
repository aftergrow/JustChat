/*************************************************************************
	> File Name: DbManager.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Tue 19 Apr 2022 09:12:24 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "DbManager.h"
#include "UserInfo.h"
#include "RelationInfo.h"
#include "MessageInfo.h"
#include "PhotoInfo.h"
#include "proto/user_info_base.pb.h"
#include "common/ret_value.h"

#define CHANGE_DATA_M


char mysql_username[256];
char mysql_password[256];

int DbManager::Init() {
	FILE* f = fopen("mysql.ini", "r");
	if (f == NULL) {
		return FILE_CAN_NOT_OPEN;
	}
	fscanf(f, "%s", mysql_username);
	fscanf(f, "%s", mysql_password);
	fclose(f);
	//初始化数据库
	conn = mysql_init(NULL);
	if (conn == NULL) {
		return DB_CONN_INIT_FAIL;
	}  
	//连接数据库
	conn = mysql_real_connect(conn, "127.0.0.1", mysql_username, mysql_password, "ssp", 0, NULL, 0);
	if (conn == NULL) {
		return DB_CONN_CONNECT_FAIL;
	}
	return SUCCESS;
}

//执行sql语句（没有对数据解码）
int DbManager::execSql(std::string sql) {
	//不为0表示出错
	if (mysql_query(conn, sql.c_str())) {
		return DB_QUREY_FAIL;
	} else {
		/* 与mysql_store_result()相比，速度更快而且使用的内存也更少。客户端仅为当前行和通信缓冲区分配内存，
		 * 分配的内存可增加到max_allowed_packet字节。
		 * 用 mysql_store_result()，客户端会为所有行分配内存 
		 */
		result = mysql_use_result(conn);
		if(result){
			int field_count = mysql_num_fields(result);
			int row_count = mysql_num_rows(result);
			printf("rows: %d, fields: %d\n",row_count,field_count);
			while(result){
				row = mysql_fetch_row(result);
				if(row == NULL){
					printf("No More Row\n");
					break;
				}
				/* field_count保存了行内值的数目。以表 tb_user 举例
				 * row[0] 保存的是该行 user_id 的值
				 * row[1] 保存的是改行 user_info 的值
				 */
				for(int j=0;j<field_count;j++){
					printf("%s\t",row[j]);
				}
				printf("\n");
			}
			//此时检索了所有的行，所以 mysql_num_rows() 返回了结果集的总行数
			row_count = mysql_num_rows(result);
			printf("rows: %d, fields: %d\n",row_count,field_count);

		}
		mysql_free_result(result);
	}
	return 0;
}

int DbManager::GetDataBegin(std::string sql) {
	if (transection() == 1) {
		return DB_BUSY;
	}
	set_transection(1);
	int ret = mysql_query(conn, sql.c_str());
	if (ret) {
		set_transection(0);
		return DB_QUREY_FAIL;
	}
	result = mysql_use_result(conn);
	return SUCCESS;
}

int DbManager::GetUsersBegin(int usr_svr_id) {
	if (transection() == 1) {
		return DB_BUSY;
	}
	set_transection(1);
	int ret;
	if (usr_svr_id == 11) {
		ret = mysql_query(conn, "select * from tb_user1;");
	} else {
		ret = mysql_query(conn, "select * from tb_user2;");
	}
	if (ret) {
		set_transection(0);
		return DB_QUREY_FAIL;
	}
	result = mysql_use_result(conn);
	return SUCCESS;
}

int DbManager::GetDataOneByOne(RelationInfo* t) {
	if (result) {
		row = mysql_fetch_row(result);
		if (row == NULL) {
			return DB_NO_MORE_DATA;
		}
		int ret;
		ssp::RelationInfoBase pb_rela;
		char rela_info[40960];
		int len = strlen(row[1]);
		for (int i = 0; i < len/2; i++) {
			rela_info[i]=(row[1][2*i]-'a')*16+(row[1][2*i+1]-'a');
		}
		pb_rela.ParseFromArray(rela_info, 40960);
		t->FromPb(pb_rela);
	} else {		
		return DB_NO_MORE_DATA;
	}
	return SUCCESS;
}
int DbManager::GetDataOneByOne(MessageInfo* t) {
	if (result) {
		row = mysql_fetch_row(result);
		if (row == NULL) {
			return DB_NO_MORE_DATA;
		}
		ssp::MessageInfoBase pb_mess;
		char mess_info[2048];
		int len = strlen(row[1]);
		for (int i = 0; i < len/2; i++) {
			mess_info[i]=(row[1][2*i]-'a')*16+(row[1][2*i+1]-'a');
		}
		pb_mess.ParseFromArray(mess_info, 2048);
		t->FromPb(pb_mess);
	} else {		
		return DB_NO_MORE_DATA;
	}
	return SUCCESS;
}

int DbManager::GetDataOneByOne(PhotoInfo* t) {
	if (result) {
		row = mysql_fetch_row(result);
		if (row == NULL) {
			return DB_NO_MORE_DATA;
		}
		ssp::PhotoInfoBase pb_photo;
		char photo_info[50];
		int len = strlen(row[1]);
		for (int i = 0; i < len/2; i++) {
			photo_info[i]=(row[1][2*i]-'a')*16+(row[1][2*i+1]-'a');
		}
		pb_photo.ParseFromArray(photo_info, 50);
		t->FromPb(pb_photo);
	} else {		
		return DB_NO_MORE_DATA;
	}
	return SUCCESS;
}

int DbManager::GetUsersOneByOne(UserInfo* user) {
	if (result) {
		row = mysql_fetch_row(result);
		if (row == NULL) {
			return DB_NO_MORE_DATA;
		}
		//row[0]:user_id
		//row[1]:user_info,protobuf
		ssp::UserInfoBase pb_user;
		char user_info[10240];
		int len = strlen(row[1]);
		for (int i = 0; i < len/2; i++) {
			user_info[i]=(row[1][2*i]-'a')*16+(row[1][2*i+1]-'a');
		}
		pb_user.ParseFromArray(user_info, 10240);
		user->FromPb(pb_user);
	} else {		
		return DB_NO_MORE_DATA;
	}
	return SUCCESS;
}

int DbManager::GetUsersEnd() {
	mysql_free_result(result);
	set_transection(0);
	return SUCCESS;
}

int DbManager::GetDataEnd() {
	GetUsersEnd();
	return SUCCESS;
}

int DbManager::GetCurUserId(int usr_svr_id) {
	int user_id = 10001;
	int ret;
	if (usr_svr_id == 11) {
		ret = mysql_query(conn, "select value from tb_var1 where key_str='user_id';");
	} else {
		ret = mysql_query(conn, "select value from tb_var2 where key_str='user_id';");
	}
	if (ret) {
		printf("query failed with cur user_id: %d\n", ret);
		return user_id;
	} else {
		result = mysql_use_result(conn);
		if (result) {
			row = mysql_fetch_row(result);
			if (row == NULL) {
				printf("result is null with cur_user_id\n");
				return user_id;
			}
			sscanf(row[0], "%d", &user_id);
		}
		mysql_free_result(result);
	}
	return user_id;
}

int DbManager::GetCurMessId() {
	int mess_id = 100001;
	int ret = mysql_query(conn, "select value from tb_var where key_str='mess_id';");

	if (ret) {
		printf("query failed with cur mess_id: %d\n", ret);
		return mess_id;
	} else {
		result = mysql_use_result(conn);
		if (result) {
			row = mysql_fetch_row(result);
			if (row == NULL) {
				printf("result is null with cur_mess_id\n");
				return mess_id;
			}
			sscanf(row[0], "%d", &mess_id);
		}
		mysql_free_result(result);
	}
	return mess_id;
}

int DbManager::InsertUser(UserInfo* user, int usr_svr_id) {
	ssp::UserInfoBase pb_user;
	user->ToPb(pb_user);
	/* printf("user    user_name: %s\n",user->user_name());
	printf("pb_user user_name: %s\n",pb_user.user_name().c_str());
	printf("user    password: %s\n",user->password());
	printf("pb_user password: %s\n",pb_user.password().c_str()); */
	char user_id[256];
	sprintf(user_id,"%d",user->user_id());
	char user_info[10240];
	pb_user.SerializeToArray(user_info,10240);
	char user_info2[10240];
	//做一下处理避免 user_info 里出现0，数据被截断
	for(int i=0;i<pb_user.ByteSize();i++){
		int l=user_info[i]&0x000f;
		int h=(user_info[i]&0x00f0)>>4;
		user_info2[i*2]=h+'a';
		user_info2[i*2+1]=l+'a';
	}
	//字符串连接
	std::string insertSql;
	if (usr_svr_id == 11) {
		insertSql="insert into tb_user1 values ('";
	} else {
		insertSql="insert into tb_user2 values ('";
	}
	insertSql+=user_id;
	insertSql+="','";
	insertSql+=user_info2;
	insertSql+="')";

	if (transection() == 1) {
		return DB_BUSY;
	}
	set_transection(1);
	
	//printf("insert: %s\n",insertSql.c_str());
	int ret=mysql_query(conn,insertSql.c_str());
	if(ret==0){
		set_transection(0);
		return SUCCESS;
	}else{
		printf("insert user failed : %d\n",ret);
		set_transection(0);
		return DB_QUREY_FAIL;
	}
	set_transection(0);
	return SUCCESS; 
}

int DbManager::ChangeData(std::string sql) {
	if (transection() == 1) {
		return DB_BUSY;
	}
	set_transection(1);
	
	int ret=mysql_query(conn,sql.c_str());
	if(ret==0){
		set_transection(0);
		return SUCCESS;
	}else{
		printf("change data failed : %d\n",ret);
		set_transection(0);

		#ifdef CHANGE_DATA_M
		printf("check delete empty data success or not: not!\n");
		#endif

		return DB_QUREY_FAIL;
	}
	set_transection(0);
	return SUCCESS;
}

int DbManager::tb_rela_query(const char* user_id) {
	//printf("before tb_rela_query\n");
	std::string insertSql;
	insertSql="select user_id,COUNT(*) from tb_rela WHERE user_id=";
	insertSql+=user_id;

	int count;
	int ret = mysql_query(conn, insertSql.c_str());
	if(ret==0){
		result = mysql_use_result(conn);
		if(result) {
			int field_count = mysql_num_fields(result);
			int row_count = mysql_num_rows(result);
			printf("rows: %d, fields: %d\n",row_count,field_count);
			while(result){
				row = mysql_fetch_row(result);
				if(row == NULL){
					printf("No More Row\n");
					break;
				}
				/* field_count保存了行内值的数目。以表 tb_user 举例
				* row[0] 保存的是该行 user_id 的值
				* row[1] 保存的是改行 user_info 的值
				*/
				for(int j=0;j<field_count;j++){
					printf("%s\t",row[j]);
				}
				count = atoi(row[1]);
				printf("\n");
			}
			//此时检索了所有的行，所以 mysql_num_rows() 返回了结果集的总行数
			row_count = mysql_num_rows(result);
			printf("rows: %d, fields: %d\n",row_count,field_count);
			
			//printf("tb_rela: %s is 1\n", user_id);
		}
		mysql_free_result(result); 
		if(count == 0) {
			return DB_NO_MORE_DATA;
		} else {
			return SUCCESS;
		}
	}else{
		printf("mysql_query() ret > 0\n");
		return DB_QUREY_FAIL;
	}
	return SUCCESS;
}

int DbManager::InsertData(RelationInfo* t) {
	//printf("before InsertData\n");
	ssp::RelationInfoBase pb_rela;
	t->ToPb(pb_rela);
	char user_id[256];
	sprintf(user_id,"%d",t->user_id());
	char rela_info[40960];
	pb_rela.SerializeToArray(rela_info,40960);
	char rela_info2[40960];
	printf("pb_rela.ByteSize(): %d\n", pb_rela.ByteSize());
	for(int i=0;i<pb_rela.ByteSize();i++){
		int l=rela_info[i]&0x000f;
		int h=(rela_info[i]&0x00f0)>>4;
		rela_info2[i*2]=h+'a';
		rela_info2[i*2+1]=l+'a';
	}
	if (transection() == 1) {
		return DB_BUSY;
	}
	set_transection(1);

	int ret = tb_rela_query(user_id);
	if(ret == DB_QUREY_FAIL) {
		set_transection(0);
		return ret;
	}

	std::string changeSql;
	if(ret == DB_NO_MORE_DATA) {
		changeSql="insert into tb_rela values ('";
		changeSql+=user_id;
		changeSql+="','";
		changeSql+=rela_info2;
		changeSql+="')";
	} else {
		changeSql="update tb_rela set rela_info='";
		changeSql+=rela_info2;
		changeSql+="' where user_id=";
		changeSql+=user_id;
	}
	printf("insert/update: %s\n",changeSql.c_str());
	ret=mysql_query(conn,changeSql.c_str());
	if(ret==0){
		set_transection(0);
		return SUCCESS;
	}else{
		printf("insert/update relation failed : %d\n",ret);
		set_transection(0);
		return DB_QUREY_FAIL;
	}            
	set_transection(0);
	return SUCCESS;
}

int DbManager::InsertData(MessageInfo* t) {
	ssp::MessageInfoBase pb_mess;
	t->ToPb(pb_mess);
	char mess_id[256];
	sprintf(mess_id,"%d",t->message_id());
	char mess_info[2048];
	pb_mess.SerializeToArray(mess_info,2048);
	char mess_info2[2048];
	//做一下处理避免 mess_info 里出现0，数据被截断
	for(int i=0;i<pb_mess.ByteSize();i++){
		int l=mess_info[i]&0x000f;
		int h=(mess_info[i]&0x00f0)>>4;
		mess_info2[i*2]=h+'a';
		mess_info2[i*2+1]=l+'a';
	}
	//字符串连接
	std::string insertSql;
	insertSql="insert into tb_mess values ('";
	insertSql+=mess_id;
	insertSql+="','";
	insertSql+=mess_info2;
	insertSql+="')";

	if (transection() == 1) {
		return DB_BUSY;
	}
	set_transection(1);
	
	//printf("insert: %s\n",insertSql.c_str());
	int ret=mysql_query(conn,insertSql.c_str());
	if(ret==0){
		set_transection(0);
		return SUCCESS;
	}else{
		printf("insert message failed : %d\n",ret);
		set_transection(0);
		return DB_QUREY_FAIL;
	}
	set_transection(0);
	return SUCCESS;
}

int DbManager::UpdateData(PhotoInfo* t) {
	ssp::PhotoInfoBase pb_photo;
	t->ToPb(pb_photo);
	char user_id[256];
	sprintf(user_id,"%d",t->user_id());
	char photo_info[50];
	pb_photo.SerializeToArray(photo_info,50);
	char photo_info2[50];
	//做一下处理避免 photo_info 里出现0，数据被截断
	for(int i=0;i<pb_photo.ByteSize();i++){
		int l=photo_info[i]&0x000f;
		int h=(photo_info[i]&0x00f0)>>4;
		photo_info2[i*2]=h+'a';
		photo_info2[i*2+1]=l+'a';
	}

	int ret;
	std::string changeSql;
	changeSql = "delete from tb_photo where user_id=";
	changeSql += user_id;
	ret = ChangeData(changeSql);
	if(ret != SUCCESS) {
		return ret;
	}

	//字符串连接
	std::string insertSql;
	insertSql="insert into tb_photo values ('";
	insertSql+=user_id;
	insertSql+="','";
	insertSql+=photo_info2;
	insertSql+="')";

	if (transection() == 1) {
		return DB_BUSY;
	}
	set_transection(1);
	
	//printf("update: %s\n",insertSql.c_str());
	ret=mysql_query(conn,insertSql.c_str());
	if(ret==0){
		set_transection(0);
		return SUCCESS;
	}else{
		printf("update photo failed : %d\n",ret);
		set_transection(0);
		return DB_QUREY_FAIL;
	}
	set_transection(0);
	return SUCCESS;
}

int DbManager::ChangeCurId(int user_svr_id, int cur_id, char* key_str) {
	std::string ChangeSql;
	std::string str_cur_id = std::to_string(cur_id);
	if (user_svr_id == 11) {
		ChangeSql="UPDATE tb_var1 SET value=";
	} else {
		ChangeSql="UPDATE tb_var2 SET value=";
	}
	ChangeSql += str_cur_id;
	ChangeSql += " WHERE key_str='";
	ChangeSql += key_str;
	ChangeSql += "'";
	//printf("change: %s\n",ChangeSql.c_str());
	int ret=mysql_query(conn,ChangeSql.c_str());
	if(ret==0){
		return SUCCESS;
	}else{
		printf("change value failed : %d\n",ret);
		return DB_QUREY_FAIL;
	}
	return SUCCESS;
}

int DbManager::ChangeCurId(int cur_mess_id, const char* key_str) {
	std::string ChangeSql;
	std::string str_cur_id = std::to_string(cur_mess_id);
	ChangeSql="UPDATE tb_var SET value=";
	ChangeSql += str_cur_id;
	ChangeSql += " WHERE key_str='";
	ChangeSql += key_str;
	ChangeSql += "'";
	//printf("change: %s\n",ChangeSql.c_str());
	int ret=mysql_query(conn,ChangeSql.c_str());
	if(ret==0){
		return SUCCESS;
	}else{
		printf("change value failed : %d\n",ret);
		return DB_QUREY_FAIL;
	}
	return SUCCESS;
}