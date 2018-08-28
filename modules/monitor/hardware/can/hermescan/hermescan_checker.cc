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

#include "modules/monitor/hardware/can/hermescan/hermescan_checker.h"

#include <utility>
#include <vector>

#include "modules/common/log.h"
#include "modules/common/util/string_util.h"
//#include "modules/monitor/hardware/can/hermescan/hermescan_err_str.h"

namespace apollo {
namespace monitor {
namespace hw {

const char HermesCanChecker::HERMES_CAN_NAME[] = "HERMES_CAN";

HermesCanChecker::HermesCanChecker() {
  name_ = apollo::common::util::StrCat(HERMES_CAN_NAME, "-", can_id_);
}

HardwareStatus::Status HermesCanChecker::hermescan_result_to_hw_status(
    int err_code) {
  // @todo: device not present detection in esd_can_test.
  return err_code == 0 ? HardwareStatus::OK : HardwareStatus::ERR;
}

std::string HermesCanChecker::hermescan_result_to_message(int err_code) {
  return err_code == 0 ? "OK" : bcan_get_err_msg(err_code);
}

void HermesCanChecker::run_check(std::vector<HwCheckResult> *results) {
  AINFO << "To check HERMES-CAN-" << can_id_;

  HermesCanDetails *details = new HermesCanDetails();
  int result = details->hermescan_do_test(can_id_);

  HwCheckResult rslt("CAN", hermescan_result_to_hw_status(result), details,
                     std::move(hermescan_result_to_message(result)));

  results->emplace_back(std::move(rslt));
}

}  // namespace hw
}  // namespace monitor
}  // namespace apollo
