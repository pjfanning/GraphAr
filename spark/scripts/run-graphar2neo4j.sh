#!/bin/bash
# Copyright 2022-2023 Alibaba Group Holding Limited.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


set -eu

cur_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
jar_file="${cur_dir}/../graphar/target/graphar-commons-0.1.0-SNAPSHOT-shaded.jar"

graph_info_path="${GRAPH_INFO_PATH:-/tmp/graphar/neo4j2graphar/MovieGraph.graph.yml}"
spark-submit --class com.alibaba.graphar.example.GraphAr2Neo4j ${jar_file} \
    ${graph_info_path}
