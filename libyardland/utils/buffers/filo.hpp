
#include <cstdint>

/**
 * @brief 
 * 
 */
class fifo_buffer
{
public:
    /**
     * @brief Construct a new filo buffer object.
     * 
     */
    fifo_buffer(int size = 256);

    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    std::uint8_t pop();
    /**
     * @brief 
     * 
     * @param data 
     */
    void push(std::uint8_t data);
private:
    /**
     * @brief Buffer.
     * 
     */
    std::uint8_t* buf;
    /**
     * @brief Head Pointer.
     * 
     */
    int head;
    /**
     * @brief Tail Pointer.
     * 
     */
    int tail;
    /**
     * @brief Size of the buffer.
     * 
     */
    int size;
};
