#ifndef _H_COMMON_PORT_MANAGER_H_
#define _H_COMMON_PORT_MANAGER_H_

#include <set>
#include <vector>
#include <mutex>
#include <stdint.h>

/**
* the port type
*/
enum class PortType : uint8_t
{
	PORT_TYPE_UDP,  //the udp port type
	PORT_TYPE_TCP   //the tcp port type
};

/**
* the port manager
*/
class PortManager
{
private:
	PortManager();

public:
	virtual ~PortManager();

	static PortManager* get_instance();

	/**
	* @brief initialize the udp ports
	*
	* @param start -- the start udp port, included
	* @param end -- the end udp port, excluded
	*/
	void initialize_udp_ports(uint16_t start, uint16_t end);

	/**
	* @brief get the udp port
	* @param port - the udp port returned, output parameter
	* @param type - the port type
	*
	* @return true - successful, and the returned port is in @param port
	*
	*/
	bool get_port(uint16_t& port, PortType type);

	/**
	* @brief release the port
	* @param port - the port to release
	* @return true - release successfully. false - failed
	*/
	bool release_port(uint16_t port);
	
	/**
	* @brief check if the port is available
	* @param port - the port to check
	* @param type - the port type
	*
	* @return true - the port is available, false - not available
	*/
	static bool check_available(uint16_t port, PortType type);

private:

	bool m_initialized;

	std::mutex m_mutex;

	//the available ports vector
	std::vector<uint16_t> m_available_ports;

	//the ports in use
	std::set<uint16_t> m_ports_in_use;
};

#endif