class DatabaseObject{
    public:
        DatabaseObject();
    private:
        PGconn* MapDBConnect();
        PGconn *conn;
        PGresult *res;
};

DatabaseObject::DatabaseObject(){
    conn = MapDBConnect();
}

PGconn* DatabaseObject::MapDBConnect(){
    PGconn     *conn;
    const char *conninfo = "host=localhost dbname=map user=domas";
    conn = PQconnectdb(conninfo);
    if(PQstatus(conn) == CONNECTION_OK){
        return conn;
    }

    const char *pghost = "localhost";
    const char *pgport = "5432";
    const char *pgoptions = "";
    const char *pgtty = "";
    const char *dbName = "map";
    const char *login = "domas";
    const char *pwd = "";
    conn = PQsetdbLogin(pghost, pgport, pgoptions, pgtty, dbName, login, pwd);
    if(PQstatus(conn) != CONNECTION_OK){
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        exit(1);
    }
    return conn;
}