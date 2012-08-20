#ifndef Renode_H_
#define Renode_H_

#include <Renode/Definitions.h>

#if __cplusplus
namespace RN {

	namespace Net {
		template<class T> class Addr;

		namespace Stream {
			class Addr;
			class Client;
			class Server;
			class Service;
		}; //ns Stream

		namespace Packet {
			class Addr;
			class Client;
			class Server;
			class Service;
		}; //ns Packet
	}; //ns Net

	class Poller;
}; //ns RN

extern "C" {
#endif /* __cplusplus */



#if __cplusplus
} //extern "C"
#endif /* __cplusplus */

#include <Renode/Poller.h>

#endif /* Renode_H_ */
