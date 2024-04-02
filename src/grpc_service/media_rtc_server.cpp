#include "media_rtc_server.h"

#include <iostream>

Status MediaRTCServiceImpl::get_recv_address(ServerContext* context, const RecvAddrRequest* request, 
        RecvAddrResponse* response)
{
    uint32_t addrCount = request->addr_count();

    std::cout << "request address count:" << addrCount << std::endl;

    //check the address count
    if(addrCount >= 4)
    {
        return Status::OK;
    }

    //allocate the port
    for(uint32_t i = 0; i < addrCount; i++)
    {
        
    }

    return Status::OK;
}