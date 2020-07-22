#ifndef P2P_CONNECTION_H_
#define P2P_CONNECTION_H_

#include <functional>
#include <memory>
#include <string>

#include "rtc/rtc_connection.h"
#include "rtc/rtc_manager.h"
#include "rtc/rtc_message_sender.h"

class P2PConnection : public RTCMessageSender {
 public:
  P2PConnection(RTCManager* rtc_manager,
                ConnectionSettings conn_settings,
                std::function<void(std::string)> send);
  ~P2PConnection() {}

  webrtc::PeerConnectionInterface::IceConnectionState getRTCConnectionState() {
    return _rtc_state;
  }
  std::shared_ptr<RTCConnection> getRTCConnection() { return _connection; };

 protected:
  //WebRTC
  void onIceConnectionStateChange(
      webrtc::PeerConnectionInterface::IceConnectionState new_state) override;
  void onIceCandidate(const std::string sdp_mid,
                      const int sdp_mlineindex,
                      const std::string sdp) override;

 private:
  std::shared_ptr<RTCConnection> _connection;
  std::function<void(std::string)> _send;
  webrtc::PeerConnectionInterface::IceConnectionState _rtc_state;
};

#endif
