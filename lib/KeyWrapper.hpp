#pragma once

# include "Libconfig.h"
# include <cstring>
# include <memory>

namespace LibConfig
{
  struct KeyWrapper
  {
    std::unique_ptr<char[]> data;
    size_t size;
    KeyType type;

    void dupKey(Key &other) const
    {
      other.data = new char[size];
      std::memcpy(other.data, data.get(), size);
      other.size = size;
      other.type = READ_WRITE;
    }

    void operator=(Key &&other)
    {
      size = other.size;
      type = other.type;
      data.reset((char*)other.data);
    }

    void operator=(KeyWrapper &&other)
    {
      size = other.size;
      type = other.type;
      data.reset(other.data.release());
    }

    KeyWrapper(KeyWrapper &&other)
    {
      *this = other;
    }

    KeyWrapper(Key &&other)
    {
      *this = other;
    }

    void operator=(const Key &other)
    {
      size = other.size;
      type = other.type;
      data.reset(new char[size]);
      std::memcpy(data.get(), other.data, size);
    }

    void operator=(const KeyWrapper &other)
    {
      size = other.size;
      type = other.type;
      data.reset(new char[size]);
      std::memcpy(data.get(), other.data.get(), size);
    }

    KeyWrapper(const KeyWrapper &other)
    {
      *this = other;
    }

    KeyWrapper(const Key &other)
    {
      *this = other;
    }

  };
}
