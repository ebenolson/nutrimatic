// fstdraw.cc

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
// Author: allauzen@google.com (Cyril Allauzen)
//
// \file
// Draws a binary FSTs in the Graphviz dot text format

#include "./draw-main.h"

namespace fst {

// Register templated main for common arcs types.
REGISTER_FST_MAIN(DrawMain, StdArc);
REGISTER_FST_MAIN(DrawMain, LogArc);

}  // namespace fst


int main(int argc, char **argv) {
  string usage = "Prints out binary FSTs in dot text format.\n\n  Usage: ";
  usage += argv[0];
  usage += " [binary.fst [text.fst]]\n";
  usage += "  Flags: acceptor, fontsize, height, isymbols, nodesep, numeric,\n";
  usage += "    osymbols, portrait, precision, ranksep, save_isymbols,\n";
  usage += "    save_osymbols, show_weight_one, ssymbols, title,\n";
  usage += "    vertical, width\n";

  std::set_new_handler(FailedNewHandler);
  SetFlags(usage.c_str(), &argc, &argv, true);
  if (argc > 3) {
    ShowUsage();
    return 1;
  }

  // Invokes DrawMain<Arc> where arc type is determined from argv[1].
  return CALL_FST_MAIN(DrawMain, argc, argv);
}
