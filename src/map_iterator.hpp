/*
  Copyright (c) 2014-2015 DataStax

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef __CASS_MAP_ITERATOR_HPP_INCLUDED__
#define __CASS_MAP_ITERATOR_HPP_INCLUDED__

#include "cassandra.h"
#include "iterator.hpp"
#include "value.hpp"
#include "serialization.hpp"

namespace cass {

class MapIterator : public Iterator {
public:
  MapIterator(const Value* map)
      : Iterator(CASS_ITERATOR_TYPE_MAP)
      , map_(map)
      , position_(map->buffer().data())
      , index_(-1)
      , count_(map_->count()) {}

  virtual bool next();

  const Value* key() {
    assert(index_ >= 0 && index_ < count_);
    return &key_;
  }

  const Value* value() {
    assert(index_ >= 0 && index_ < count_);
    return &value_;
  }

private:
  char* decode_pair(char* position);

private:
  const Value* map_;
  char* position_;
  Value key_;
  Value value_;
  int32_t index_;
  const int32_t count_;
};

} // namespace cass

#endif
