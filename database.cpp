typedef std::map<std::string, char*> row;

class DatabaseObject{
    public:
        DatabaseObject();
        std::vector<row> select(std::string);
    private:
        PGconn* MapDBConnect();
        PGconn *conn;
        PGresult *res;
};

std::vector<row> DatabaseObject::select(std::string query){
    std::vector<row> rows;
    if(query.find("select") != 0){
        query = "select " + query;
    }
    res = PQexec(conn, query.c_str());
    if(PQresultStatus(res) == PGRES_TUPLES_OK){
        int row_count = PQntuples(res);
        int col_count = PQnfields(res);
        for(int i=0; i<row_count; i++){
            row r;
            for(int j=0; j<col_count; j++){
                if(!PQgetisnull(res, i, j)){
                    r[PQfname(res, j)] = PQgetvalue(res, i, j);
                }
            }
            rows.push_back(r);
        }
    }

    PQclear(res);
    return rows;
}

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