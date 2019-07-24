#ifndef BUFFER_SAVERS_HPP
#define BUFFER_SAVERS_HPP

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <memory>
#include <functional>


template<typename ... Args> std::string string_format(const std::string& format, Args ... args)
{
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]); 
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}


template <class T> void WriteBinaryArray(const std::string& filename, 
  const std::string& name, unsigned long tag, const T* buffer, int bufferLen)
{
  std::ofstream f(filename, std::ios::out | std::ios::binary);
  f.write(reinterpret_cast<const char *>(&tag), sizeof(tag));
  f.write(reinterpret_cast<const char *>(buffer), bufferLen*sizeof(T));
}


template <class T> void WriteFormattedArray(const std::string& filename, 
  const std::string& name, unsigned long tag, const T* buffer, int bufferLen)
{
  std::ofstream f(filename, std::ios::out);

  f << name << " tag: " << tag << "\n";
  for (int i = 0; i < bufferLen; i++) {
    f << buffer[i];
    if (i < bufferLen-1) {
      f << ", ";
    }
    f << "\n";
  }
  f << "\n";
}


template <class T> class BufferSaver {
public:
  BufferSaver(const std::string& name, int maxNumSavedBuffers, int bufferLen, bool saveTheBuffers)
  : m_name(name),
    m_saveTheBuffers(saveTheBuffers),
    m_maxNumSavedBuffers(maxNumSavedBuffers), 
    m_bufferLen(bufferLen), 
    m_bufferSize(bufferLen*sizeof(T)),
    m_savedBuffers(nullptr),
    m_nextBufferNum(0) 
  {
  }

  ~BufferSaver() 
  {
    DeallocateBuffers();
  }

  void SetLogger(std::function<void (int, const std::string&)> logger) { m_logger = logger; }
  void SetSave(bool saveBuffers) { m_saveTheBuffers = saveBuffers; }

  void Save(const T* buffer, unsigned long tag) 
  {
    if (!m_saveTheBuffers) {
      return;
    }
    if (m_savedBuffers == nullptr) {
      AllocateBuffers();
      m_nextBufferNum = 0;
    }

    memcpy(m_savedBuffers[m_nextBufferNum].buffer, buffer, m_bufferSize);
    m_savedBuffers[m_nextBufferNum].tag = tag;
    m_nextBufferNum++;
  }

  void Write(const char* filenameTemplate, bool binaryFormat) const
  {
    if (!m_saveTheBuffers) {
      return;
    }
    Log(0, string_format("BufferSaver::Write: Saving %d saved buffers...", m_nextBufferNum));
    for (int i = 0; i < m_nextBufferNum; i++) {
      char filename[200];
      sprintf(filename, filenameTemplate, i);

      if (binaryFormat) {
        WriteBinaryArray(filename, m_name, m_savedBuffers[i].tag, m_savedBuffers[i].buffer, m_bufferLen);
      } else {
        WriteFormattedArray(filename, m_name, m_savedBuffers[i].tag, m_savedBuffers[i].buffer, m_bufferLen);
      }
    }
  }

private:
  void Log(int severity, const std::string& msg) const
  {
      if (m_logger == nullptr)
          return;
      m_logger(severity, msg);    
  }

  void AllocateBuffers()
  {
    m_savedBuffers = new BufferData[m_maxNumSavedBuffers];
    for (int i = 0; i < m_maxNumSavedBuffers; i++) {
      m_savedBuffers[i].buffer = new T[m_bufferLen];
      if (!m_savedBuffers[i].buffer) {
        Log(0, string_format("BufferSaver::Save: Could not allocate saved buffer %d.", i));
        break;
      }
      m_savedBuffers[i].tag = 0;
    }
  }

  void DeallocateBuffers()
  {
    if (m_savedBuffers == nullptr) {
      return;
    }
    
    for (int i = 0; i < m_maxNumSavedBuffers; i++) {
      delete[] m_savedBuffers[i].buffer;
    }
    delete[] m_savedBuffers;
  }

private:
  const std::string m_name;
  bool m_saveTheBuffers;
  const int m_bufferLen;  
  const size_t m_bufferSize;
  const int m_maxNumSavedBuffers;
  struct BufferData {
    T* buffer;
    unsigned long tag;
  };
  BufferData* m_savedBuffers;
  int m_nextBufferNum;

  std::function<void (int, const std::string&)> m_logger;
};


#endif
