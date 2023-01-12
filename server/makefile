all:prot config common_o socket db bus user rela photo mess dbt usr svr cln
all1:config common_o socket db bus user rela photo mess dbt usr svr cln
dbg:db usr svr cln
connect_test:
	g++ -o qt_connect_test config.o socket.o qt_connect_test.cpp

prot:
	cd ./proto && make
config:
	g++ -c -o config.o Config.cpp
common_o:
	g++ -c -o common_o.o common.cpp
socket:
	g++ -c -o socket.o Socket.cpp
db:
	g++ -c -o db.o DbManager.cpp
bus:
	g++ -c -o bus.o BusManager.cpp
	g++ -o bus_test bus.o bus_test.cpp 
user:
	g++ -c -o userM.o UserManager.cpp
	g++ -c -o userI.o UserInfo.cpp
rela:
	g++ -c -o relaI.o RelationInfo.cpp
	g++ -c -o relaM.o RelationManager.cpp
mess:
	g++ -c -o messI.o MessageInfo.cpp
	g++ -c -o messM.o MessageManager.cpp
photo:
	g++ -c -o photoI.o PhotoInfo.cpp
	g++ -c -o photoM.o PhotoManager.cpp	 
dbt:
	g++ -o dbtest config.o socket.o db.o userM.o userI.o relaI.o relaM.o messI.o messM.o photoI.o photoM.o proto/*.o dbmain.cpp -lmysqlclient -lprotobuf
usr:
	g++ -o user_svr proto/*.o config.o common_o.o socket.o db.o bus.o userM.o userI.o relaI.o relaM.o messI.o messM.o photoI.o photoM.o user_svr.cpp -lprotobuf -lmysqlclient
svr:
	g++ -o server_ssp *.o proto/*.o server.cpp reactor.cpp -lprotobuf -lmysqlclient -lpthread
cln:
	g++ -o client_ssp proto/*.o *.o 2client.cpp -lprotobuf -lmysqlclient
	g++ -o client_ssp_c proto/*.o *.o client.cpp -lprotobuf -lmysqlclient
clean:
	rm -f *.o ./proto/*.o ./proto/*.pb.h ./proto/*.pb.cc server_ssp client_ssp
clean1:
	rm -f *.o ./proto/*.o server_ssp client_ssp
clean2:
	rm -f *.o server_ssp client_ssp