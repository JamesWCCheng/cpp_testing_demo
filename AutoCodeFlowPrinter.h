#ifndef auto_code_flow_printer_h
#define auto_code_flow_printer_h
#include <stdio.h>
 #ifdef MOZ_WIDGET_GONK
  #include "android/log.h"
  #define LOGX(args...) \
      __android_log_print(ANDROID_LOG_INFO, "James" , ## args) \
      printf(args);
  #else
    #define LOGX(args...) \
    printf(args);
#endif

class AutoCodeFlowPrinter
{
public:
  AutoCodeFlowPrinter(const char* aFunction, const char* aFile,  const int aLine)
  : mFunction(aFunction), mFile(aFile), mLine(aLine)
  {
    LOGX("++++++++++Enter  %s at %s : %d ++++++++++ \n", aFunction, aFile, aLine);
  }
  ~AutoCodeFlowPrinter()
  {
    LOGX("------------------Leave %s at %s ------------------ \n", mFunction, mFile);
  }
  AutoCodeFlowPrinter(const AutoCodeFlowPrinter& rhs) = delete;
  AutoCodeFlowPrinter& operator = (const AutoCodeFlowPrinter& rhs) = delete;
private:
  const char* mFunction;
  const char* mFile;
  int mLine;
};

#define ACFP AutoCodeFlowPrinter(__FUNCTION__, __FILE__, __LINE__)
#endif

