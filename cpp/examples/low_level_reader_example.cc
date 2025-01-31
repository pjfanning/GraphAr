/*
 * Copyright 2022-2023 Alibaba Group Holding Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>

#include "arrow/api.h"
#include "arrow/filesystem/api.h"

#include "./config.h"
#include "gar/api.h"
#include "gar/reader/chunk_info_reader.h"

void vertex_property_chunk_info_reader(
    const std::shared_ptr<GAR_NAMESPACE::GraphInfo>& graph_info) {
  // constuct reader
  std::string label = "person", property_name = "id";
  auto maybe_reader = GAR_NAMESPACE::VertexPropertyChunkInfoReader::Make(
      graph_info, label, property_name);
  ASSERT(!maybe_reader.has_error());
  auto reader = maybe_reader.value();

  // use reader
  auto maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  std::string chunk_path = maybe_chunk_path.value();
  std::cout << "path of first vertex property chunk: " << chunk_path
            << std::endl;
  // seek vertex id
  ASSERT(reader->seek(520).ok());
  maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  chunk_path = maybe_chunk_path.value();
  std::cout << "path of vertex property chunk for vertex id 520: " << chunk_path
            << std::endl;
  // next chunk
  ASSERT(reader->next_chunk().ok());
  maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  chunk_path = maybe_chunk_path.value();
  std::cout << "path of next vertex property chunk: " << chunk_path
            << std::endl;
  std::cout << "vertex property chunk number: " << reader->GetChunkNum()
            << std::endl;
}

void adj_list_chunk_info_reader(
    const std::shared_ptr<GAR_NAMESPACE::GraphInfo>& graph_info) {
  // construct reader
  std::string src_label = "person", edge_label = "knows", dst_label = "person";
  auto maybe_reader = GAR_NAMESPACE::AdjListChunkInfoReader::Make(
      graph_info, src_label, edge_label, dst_label,
      GAR_NAMESPACE::AdjListType::ordered_by_source);
  ASSERT(maybe_reader.status().ok());
  auto reader = maybe_reader.value();

  // use reader
  auto maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  auto chunk_path = maybe_chunk_path.value();
  std::cout << "path of first adj_list chunk: " << chunk_path << std::endl;
  // seek src
  ASSERT(reader->seek_src(100).ok());
  maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  chunk_path = maybe_chunk_path.value();
  std::cout
      << "path of fisrt adj_list chunk for outgoing edges of vertex id 100: "
      << chunk_path << std::endl;
  // next chunk
  ASSERT(reader->next_chunk().ok());
  maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  chunk_path = maybe_chunk_path.value();
  std::cout << "path of next adj_list chunk: " << chunk_path << std::endl;
}

void adj_list_property_chunk_info_reader(
    const std::shared_ptr<GAR_NAMESPACE::GraphInfo>& graph_info) {
  // construct reader
  std::string src_label = "person", edge_label = "knows", dst_label = "person",
              property_name = "creationDate";

  auto maybe_property_reader =
      GAR_NAMESPACE::AdjListPropertyChunkInfoReader::Make(
          graph_info, src_label, edge_label, dst_label, property_name,
          GAR_NAMESPACE::AdjListType::ordered_by_source);
  ASSERT(maybe_property_reader.status().ok());
  auto reader = maybe_property_reader.value();

  // use reader
  auto maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  auto chunk_path = maybe_chunk_path.value();
  std::cout << "path of first adj_list property chunk: " << chunk_path
            << std::endl;
  // seek src
  ASSERT(reader->seek_src(100).ok());
  maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  chunk_path = maybe_chunk_path.value();
  std::cout << "path of fisrt adj_list property chunk for outgoing edges of "
               "vertex id 100: "
            << chunk_path << std::endl;
  // next chunk
  ASSERT(reader->next_chunk().ok());
  maybe_chunk_path = reader->GetChunk();
  ASSERT(maybe_chunk_path.status().ok());
  chunk_path = maybe_chunk_path.value();
  std::cout << "path of next adj_list property chunk: " << chunk_path
            << std::endl;
}

int main(int argc, char* argv[]) {
  // read file and construct graph info
  std::string path =
      TEST_DATA_DIR + "/ldbc_sample/parquet/ldbc_sample.graph.yml";
  auto graph_info = GAR_NAMESPACE::GraphInfo::Load(path).value();

  // vertex property chunk info reader
  std::cout << "Vertex property chunk info reader" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  vertex_property_chunk_info_reader(graph_info);
  std::cout << std::endl;

  // adj_list chunk info reader
  std::cout << "Adj_list chunk info reader" << std::endl;
  std::cout << "--------------------------" << std::endl;
  adj_list_chunk_info_reader(graph_info);
  std::cout << std::endl;

  // adj_list property chunk info reader
  std::cout << "Adj_list property chunk info reader" << std::endl;
  std::cout << "-----------------------------------" << std::endl;
  adj_list_property_chunk_info_reader(graph_info);
}
