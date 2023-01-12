/*************************************************************************
	> File Name: dbmain.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Wed 20 Apr 2022 05:24:16 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "DbManager.h"

DbManager db_svr;
int main() {
	db_svr.Init();
	//truncate：删除表中的内容，不删除表结构，释放空间
	db_svr.execSql("truncate tb_user;");
	//执行这条语句 mysql_query() 函数将返回非0值。同时数据将插入表中
	//注：查询语句不用加分号
	db_svr.execSql("insert into tb_user values ( '10001', 'mark' )");
	db_svr.execSql("insert into tb_user values ( '10002', 'mark2')");
	db_svr.execSql("insert into tb_user values ( '10003', 'mark3')");
	db_svr.execSql("select * from tb_user;");

	return 0;
}