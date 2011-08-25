/*
Initial fcgi/sqlite3/json 
11825
creamy.mobi
Waitman Gobble
waitman@waitman.net
+1.6503967580
gcc -o json json.c -I/usr/local/include -L/usr/local/lib -lfcgi -lsqlite3 -ljson

http://fcgi.creamy.mobi/pub/json
*/
#include <fcgi_stdio.h>
#include <json/json.h>
#include <sqlite3.h>


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  NotUsed=0;

json_object * jobj = json_object_new_object();

  for(i=0; i<argc; i++){
	json_object *jstring = json_object_new_string(argv[i] ? argv[i] : "NULL");
	json_object_object_add(jobj,azColName[i],jstring);
  }
	printf ("%s\n",json_object_to_json_string(jobj));
  return 0;
}

int main( int argc, char *argv[] )
{

sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

   while( FCGI_Accept() >= 0 ) {
      printf( "Content-Type: text/plain\n\n" );

rc = sqlite3_open("test.db", &db);
  if( rc ){
    printf("Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
  }
  rc = sqlite3_exec(db, "SELECT * FROM uu LIMIT 0,1", callback, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    printf("SQL error: %s\n", zErrMsg);
  }
  sqlite3_close(db);


   }
   return 0;
}
