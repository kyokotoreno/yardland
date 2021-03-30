/**
 * @file fifo.cpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @brief 
 * @version 0.1.0
 * @date 2021-03-28
 * 
 * This code was taken from the implementation of this site: <em> https://blog.stratifylabs.co/device/2013-10-02-A-FIFO-Buffer-Implementation/#:~:text=A%20FIFO%20buffer%20is%20a,requirements%20for%20the%20embedded%20firmware. </em>
 *
 * @copyright Copyright (c) 2021
 * 
 */

#include <libyardland/utils/buffers/fifo.hpp>

fifo_buffer::fifo_buffer(int size)
{
    this->buf = ( std::uint8_t* ) std::malloc (size * sizeof(std::uint8_t));
    return;
}

std::uint8_t fifo_buffer::pop()
{
    std::uint8_t data = 0;

    if (this->tail != this->head) { //see if any data is available
        data = this->buf[this->tail];  //grab a byte from the buffer
        
        this->tail++;  //increment the tail

        if (this->tail == this->size) {  //check for wrap-around
            this->tail = 0;
        }
    }

    return data;
}

void fifo_buffer::push(std::uint8_t data)
{
    //first check to see if there is space in the buffer
    if((this->head + 1 == this->tail) ||
        ((this->head + 1 == this->size) && (this->tail == 0))){
            return; //no more room
    } else {
        this->buf[this->head] = data;

        this->head++;  //increment the head

        if( this->head == this->size ){  //check for wrap-around
            this->head = 0;
        }
    }

    return;
}
