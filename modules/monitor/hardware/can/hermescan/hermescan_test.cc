/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/monitor/hardware/can/hermescan/hermescan_test.h"

#include <ostream>

#include "modules/common/log.h"
//#include "modules/monitor/hardware/can/hermescan/hermescan_err_str.h"

namespace apollo {
namespace monitor {
namespace hw {

int HermesCanDetails::hermescan_do_test(int id) {
  bcan_hdl_t h0;
  int ret;

  invalidate();

  ret = bcan_open(id, 0, 0, 0, &h0);
  if (ret == 0) {
    AINFO << "Successfully opened HERMES-CAN device " << id;

    ret = bcan_get_status(h0);
    if (ret != 0) {
      AERROR << "Cannot get status of HERMES-CAN device " << id
             << ", ret=" << ret << " (" << bcan_get_err_msg(ret) << ")";
      goto err;
    }

    AINFO << "Got HERMES-CAN-" << id << " interface status";
//    add_valid_field(HermesCanDetails::IF_STATUS);
    // else: fall-out to continue
  } else {
    AERROR << "Failed to open HERMES-CAN device " << id
           << ", error: " << ret << " (" << bcan_get_err_msg(ret) << ")";
    goto err;
  }

//  ret = canIoctl(h0, , &stats);
//  if (ret != 0) {
//    AERROR << "NTCAN_IOCTL_GET_BUS_STATISTIC failed for device " << id
//           << " with error: " << ret << " (" << bcan_get_err_msg(ret) << ")";
//   goto err;

//  }
  // add_valid_field(HermesCanDetails::STATS);
  AINFO << "Got HERMES-CAN-" << id << " statistics";

  // ret = canIoctl(h0, NTCAN_IOCTL_GET_CTRL_STATUS, &ctrl_state);
  // if (ret != NTCAN_SUCCESS) {
  //   AERROR << "NTCAN_IOCTL_GET_CTRL_STATUS failed for device " << id
  //          << "with error: " << ret << " (" << esdcan_err_to_str(ret) << ")";
  //   goto err;
  // }
  // add_valid_field(EsdCanDetails::CTRL_STATE);
  AINFO << "Got ESD-CAN-" << id << " strl-state";

  uint32_t bitrate;
  ret = bcan_get_baudrate(h0, &bitrate);
  if (ret != 0) {
    AERROR << "bcan_get_baudrate for device " << id
           << " with error: " << ret << " (" << bcan_get_err_msg(ret) << ")";
    goto err;
  }
  // add_valid_field(EsdCanDetails::BITRATE);
  AINFO << "Got HERMES-CAN-" << id << " bitrate";

err:
  bcan_close(h0);
  result = ret;
  return ret;
}

 void HermesCanDetails::print_summary(std::ostream &os) {
   if (result == 0) {
     os << "HERMES-CAN test PASSED, CAN bus statistics:\n"
//        << "Rcv frames      : Std(Data/RTR): " << stats.rcv_count.std_data << "/"
//        << stats.rcv_count.std_rtr
//        << ", Ext(Data/RTR): " << stats.rcv_count.ext_data << "/"
//        << stats.rcv_count.ext_rtr << std::endl
//        << "Xmit frames     : Std(Data/RTR): " << stats.xmit_count.std_data
//        << "/" << stats.xmit_count.std_rtr
//        << ", Ext(Data/RTR): " << stats.xmit_count.ext_data << "/"
//        << stats.xmit_count.ext_rtr << std::endl
//        << "Bytes           : (Rcv/Xmit): " << stats.rcv_byte_count << "/"
//        << stats.xmit_byte_count << std::endl
//        << "Overruns        : (Controller/FIFO): " << stats.ctrl_ovr << "/"
//        << stats.fifo_ovr << std::endl
//        << "Err frames      : " << stats.err_frames << std::endl
//        << "Aborted frames  : " << stats.aborted_frames << std::endl
//        << "Err counter     : (Rx/Tx): "
//        << static_cast<int>(ctrl_state.rcv_err_counter) << "/"
//        << static_cast<int>(ctrl_state.xmit_err_counter) << std::endl
//        << "Status          : " << std::hex
//        << static_cast<int>(ctrl_state.status) << std::endl
//        << "Rcv bits        : " << std::dec << stats.bit_count 
     << std::endl;
   } else {
     os << "ESD-CAN test FAILED with error " << result << ": "
        << bcan_get_err_msg(result) << std::endl;
   }
 }

 void HermesCanDetails::print_test_result(std::ostream &os) {
   if (result == 0) {
     os << "HERMES-CAN test PASSED\n" << std::endl;
   } else {
     os << "HERMES-CAN test FAILED with error " << result << ": "
        << bcan_get_err_msg(result) << std::endl;
   }
 }

}  // namespace hw
}  // namespace monitor
}  // namespace apollo
