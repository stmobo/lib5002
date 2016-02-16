#include "wpilib_cameraserver.h"
#include "network_bytestream.h"
#include "opencv2/highgui.hpp"

/*
 * WPILib CameraServer network format:
 * Port: TCP 1180
 * 
 * Server waits for client to transmit:
 * - desired FPS
 * - desired compression (only accepted value: -1)
 * - desired size (out of cs_imgSize enum)
 * Server then continually transmits:
 * - Protocol header (4 bytes): 0x01 0x00 0x00 0x00
 * - Data length (4 bytes), int
 * - JPEG image data
 */

connSocket connectToCamServer(netaddr serverAddress,
	int fps, cs_imgSize sz) {

	serverAddress.setPort(cs_port);

	nbstream opening;
	opening.put32(fps);
	opening.put32(static_cast<uint32_t>(-1));
	opening.put32(static_cast<unsigned int>(sz));

	netmsg msg(opening.tobuf(), opening.getbufsz(), SOCK_STREAM);

	connSocket cs_connection(serverAddress);
	cs_connection.send(msg);

	return cs_connection;
}

cv::Mat getImageFromServer(connSocket& cs_socket) {
	while(true) {	
		netmsg camdata = cs_socket.recv(864000+8); // 600 * 480 * 3 bytes of JPEG data at max + 8 bytes of header

		nbstream is(camdata.getbuf(), camdata.getnetsz());
		unsigned char header[4] = { is.get8(), is.get8(), is.get8(), is.get8() };

		bool valid_header = true;
		for(int i=0;i<4;i++) {
			if(header[i] != cs_header[i]) {
				valid_header = false;
				break;		
			}
		}

		if(!valid_header) {
			continue;
		}

		std::vector<unsigned char> jpegdata(is.cur, is.buf.end());
		return cv::imdecode(jpegdata, CV_LOAD_IMAGE_COLOR);
	}
}