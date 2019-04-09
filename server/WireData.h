#ifndef SERVER_WIREDATA_H
#define SERVER_WIREDATA_H

#include <microhttpd.h>
#include <cstring>
#include <string>
#include <iostream>

namespace server {

class WireData
{
public:
    WireData(struct MHD_Connection *connection,
             const char *url,
             const char *method, const char *version,
             const char *upload_data,
             size_t *upload_data_size)
        : _connection(connection)
        , _url(url)
        , _method(method)
        , _version(version)
        , _upload_data(upload_data)
        , _upload_data_size(upload_data_size)
    {}

    struct MHD_Connection * getConnection() const { return _connection; }
    std::string getUrl() const { return _url; }
    std::string getMethod() const { return _method; }
    std::string getVersion() const { return _version; }
    std::string getUploadData() const { return _upload_data; }

public:
    struct MHD_Connection * _connection;
    std::string _url;
    std::string _method;
    std::string _version;
    const char * _upload_data;
    const size_t * _upload_data_size;


};

std::ostream& operator << (std::ostream& stream, const WireData& wire)
{
//    MHD_get_connection_values(connection, )
    stream << wire.getMethod() << ", " << std::endl
           << wire.getUrl()    << ", " << std::endl
           //<< (wire._upload_data ? wire._upload_data : ""    << ", ") << std::endl
           << *(wire._upload_data_size)    << ", " << std::endl
           //<< strlen(wire._upload_data)    << ", " << std::endl
           << wire.getVersion() << ", " << std::endl;
    if (wire._upload_data) stream << wire._upload_data << ", " << std::endl;
    return stream;
}


} // namespace server

#endif // SERVER_WIREDATA_H
