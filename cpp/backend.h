/* Copyright 2019 The MLPerf Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef MLPERF_BACKEND_H_
#define MLPERF_BACKEND_H_

#include <vector>

#include "cpp/utils.h"
#include "loadgen/system_under_test.h"

namespace mlperf {
namespace mobile {

// Backend is an interface adapting different backends for MLPerfDriver.
// This interface is the same as SystemUnderTest but the ReportLatencyResults
// method is already handled by MLPerfDriver and it has methods for setting
// input and returning predicted output.

class Backend {
 public:
  Backend() {}

  virtual ~Backend() {}

  // A human-readable string for logging purposes.
  virtual const std::string& Name() const = 0;

  // Run inference for a sample. Inputs is already set by SetInputs.
  virtual void IssueQuery() = 0;

  // Flush the staged queries immediately.
  virtual void FlushQueries() = 0;

  // Sets inputs for a sample before inferencing.
  virtual void SetInputs(const std::vector<void*>& inputs) = 0;

  // Returns the result after inferencing.
  virtual std::vector<void*> GetPredictedOutputs() = 0;

  // Returns the input format required by the model.
  virtual const DataFormat& GetInputFormat() = 0;

  // Returns the output format produced by the model.
  virtual const DataFormat& GetOutputFormat() = 0;
};

}  // namespace mobile
}  // namespace mlperf
#endif  // MLPERF_BACKEND_H_
