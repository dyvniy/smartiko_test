#include "dbworker.h"
#include <pqxx/pqxx>
#include <iostream>
#include <sstream>
#include <vector>

struct DbWorker::Impl{
    pqxx::connection* pConn{nullptr};

    Impl() {
        pConn = new pqxx::connection("user=postgres password=123456 host=172.17.0.3 port=5432 "
                                 "dbname=postgres target_session_attrs=read-write");
        std::cout << pConn << std::endl;
        std::cout << pConn->server_version() << std::endl;
    }
    ~Impl() {
        delete pConn;
    }

    bool exec(std::string query)
    {
        pqxx::work xact(*pConn, "SampleSelect");
        pqxx::result res;
        try {
            res = xact.exec(query);
            xact.commit();
        } catch (pqxx::pqxx_exception& e) {
            std::cerr << "Failed to execute query: " << query
                      << std::endl << e.base().what() << std::endl;
            return false;
        } catch (...) {
            std::cerr << "Failed to execute query: " << query << std::endl;
            return false;
        }
        return true;
    }

    static std::vector<std::string> parse(std::string data, char separator = ';')
    {
        std::vector<std::string> params;
        std::istringstream f(data);
        std::string s;
        while (getline(f, s, separator)) {
            // std::cout << s << std::endl;
            params.push_back(s);
        }
        return params;
    }

};

DbWorker::DbWorker()
    :pImpl(new Impl())
{
    create();
}

DbWorker::~DbWorker()
{

}

bool DbWorker::create()
{
    std::string query{
        "CREATE TABLE IF NOT EXISTS readingsb ("
        "id SERIAL PRIMARY KEY, "
        "name character varying(100), "
        "gpoup numeric(5,3), "
        "acure_d date, "
        "acure_t time without time zone, "
        "graduated boolean)"};
    return pImpl->exec(query);
}



bool DbWorker::insert(std::string data)
{
    std::vector<std::string> params = pImpl->parse(data);
    std::string query{"INSERT INTO public.readingsb("
                      "name, gpoup, acure_d, acure_t, graduated) "
                      "VALUES ("};
    // looks like "VALUES ('val02', 89.90, '2021/12/28', '16:24', False);";
    for (int i=1; i<params.size(); ++i){
        query += params[i];
    }
    query += ")";
    pImpl->exec(query);
    return true;
}

bool DbWorker::get(std::string data)
{
    std::vector<std::string> params = pImpl->parse(data);
    std::string query{"SELECT * FROM public.readingsb"};
    pqxx::work xact(*pImpl->pConn, "SampleSelect");
    pqxx::result res;
    try {
        // fields "name, gpoup, acure_d, acure_t, graduated)"

        // looks like "name = 'value1' AND group < 3;"
        if (params.size() > 1){
             query += " WHERE ";
        }
        for (int i=1; i<params.size(); ++i){
            query += params[i];
        }
        query += ";";

        res = xact.exec(query);

        // Show results
        for (pqxx::result::const_iterator i = res.begin(), r_end = res.end(); i != r_end; ++i) {
            // Iterate fields
            for (pqxx::row::const_iterator f = i->begin(), f_end = i->end(); f != f_end; ++f) {
                std::cout << f->name() << " = '" << f->c_str() << "'" << std::endl;
            }
            std::cout << std::endl;
        }
    } catch (...) {
        std::cerr << "Failed to execute query: " << query << std::endl;
    }
    return true;
}

bool DbWorker::delete_(std::string data)
{
    std::vector<std::string> params = pImpl->parse(data);
    std::string query{"DELETE FROM public.readingsb WHERE "};
    // fields "name, gpoup, acure_d, acure_t, graduated)"

    // looks like "name = 'value1' AND group < 3;"
    for (int i=1; i<params.size(); ++i){
        query += params[i];
    }
    query += ";";
    pImpl->exec(query);
    return true;
}

bool DbWorker::exec(boost::property_tree::ptree pt)
{
    try {
        auto method = pt.get<std::string>("method");
        if (method.find("GET") == 0) {
            return get(pt);
        } else if (method.find("POST") == 0) {
            return insert(pt);
        } else if (method.find("DELETE") == 0) {
            return delete_(pt);
        } else {
            std::cerr << "unknown method in json request" << std::endl;
        }
    } catch (...) {
        std::cerr << "error in DbWorker::exec, " << std::endl;
        return false;
    }

    return true;
}

bool DbWorker::insert(boost::property_tree::ptree pt)
{
    return false;
}

bool DbWorker::get(boost::property_tree::ptree pt)
{
    return false;
}

bool DbWorker::delete_(boost::property_tree::ptree pt)
{
    return false;
}

bool DbWorker::insert(std::string dbname, dataPairs data)
{
    return false;
}

bool DbWorker::get(std::string dbname, dataPairs where)
{
    return false;
}

bool DbWorker::delete_(std::string dbname, dataPairs where)
{
    return false;
}
