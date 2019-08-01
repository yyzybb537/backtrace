
namespace backtrace {
    // 获取堆栈信息
    char* getBacktrace();

    // 设置采样率, 默认1(全量)
    // 例如：0.001表示千分之一采样
    void setRatio(double ratio);
}

