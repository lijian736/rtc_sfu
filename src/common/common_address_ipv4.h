#ifndef _H_COMMON_IP_ADDRESS_V4_H_
#define _H_COMMON_IP_ADDRESS_V4_H_

#include <string>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>

//ipv4 destination address
class IPAddrV4
{
public:

	/**
	* @brief constructor
	* @param ip -- the ip address
	* @param port -- the port, in host byte order
	*/
	IPAddrV4(const char* ip, const uint16_t& port);
	IPAddrV4(const std::string &ip, const uint16_t& port);

	virtual ~IPAddrV4();

	bool operator ==(const IPAddrV4 &rhs) const;
	bool equals(const std::string& ip, const uint16_t& port);
	const struct sockaddr_in* get_sock_addr() const;

	/**
	 * @brief Get the ip address
	 * 
	 * @return std::string the ip address
	 */
	std::string get_ipaddr();

	/**
	 * @brief get the port in host byte order
	 * 
	 *
	 * @return uint16_t, the port in host byte order
	 */
	uint16_t get_port();

private:
	struct sockaddr_in m_sock_addr;

	std::string m_ipaddr;
	//port in host byte order
	uint16_t m_port;
};

#endif
