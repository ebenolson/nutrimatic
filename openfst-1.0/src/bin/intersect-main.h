// intersect-main.h

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: riley@google.com (Michael Riley)
//
// \file
// Intersects two FSAs. Includes helper function for fstintersect.cc
// that templates the main on the arc type to support multiple and
// extensible arc types.
//

#ifndef FST_INTERSECT_MAIN_H__
#define FST_INTERSECT_MAIN_H__

#include <fst/intersect.h>
#include <fst/main.h>
#include <fst/vector-fst.h>

DECLARE_bool(connect);

namespace fst {

// Main function for fstintersect templated on the arc type.
// Call only with 'return CALL_FST_MAIN' in main().
template <class Arc>
int IntersectMain(int argc, char **argv, istream &strm,
             const FstReadOptions &opts) {
  Fst<Arc> *ifst1 = Fst<Arc>::Read(strm, opts);
  if (!ifst1) return 1;

  if ((opts.source == "standard input" && strcmp(argv[2], "-") == 0)
      || strcmp(argv[2], "") == 0) {
    LOG(ERROR) << argv[0] << ": Can't open file: " << argv[2];
    return 1;
  }
  Fst<Arc> *ifst2 = Fst<Arc>::Read(strcmp(argv[2], "-") != 0 ? argv[2] : "");
  if (!ifst2) return 1;

  IntersectOptions iopts(FLAGS_connect);
  VectorFst<Arc> ofst;
  Intersect(*ifst1, *ifst2, &ofst, iopts);
  ofst.Write(argc > 3 ? argv[3] : "");

  return 0;
}

}  // namespace fst

#endif  // FST_INTERSECT_MAIN_H__
