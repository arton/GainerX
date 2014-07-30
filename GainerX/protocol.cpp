#include "stdafx.h"
#include "protocol.h"

Context::fsm_t Context::fsmdef[] = {
    FSM_CHR_ITEM(IDLE, 'F', NULL, BTN_R),
    FSM_CHR_ITEM(IDLE, 'N', NULL, BTN_P),
    FSM_CHR_ITEM(WAIT_RESP, 'F', NULL, BTN_R),
    FSM_CHR_ITEM(WAIT_RESP, 'N', NULL, BTN_P),
    FSM_CHR_ITEM(BTN_R, '*', &button_released, IDLE),
    FSM_CHR_ITEM(BTN_P, '*', &button_pressed, IDLE),
    FSM_CHR_ITEM(WAIT_LAST, '*', NULL, IDLE),
    //
    FSM_CHR_ITEM(WAIT_RESP, 'h', NULL, WAIT_LAST),
    FSM_CHR_ITEM(IDLE, 'h', NULL, WAIT_LAST),
    FSM_CHR_ITEM(WAIT_RESP, 'l', NULL, WAIT_LAST),
    FSM_CHR_ITEM(IDLE, 'l', NULL, WAIT_LAST),
    FSM_CHR_RANGE_ITEM(DATA_SEQ, '0', '9', &data_seq, DATA_SEQ),
    FSM_CHR_RANGE_ITEM(DATA_SEQ, 'A', 'F', &data_seq, DATA_SEQ),
    FSM_CHR_ITEM(DATA_SEQ, '*', &data_end, IDLE),
    FSM_CHR_ITEM(WAIT_RESP, 'A', NULL, DROP_SEQ),
    FSM_CHR_ITEM(IDLE, 'A', NULL, DROP_SEQ),
    FSM_CHR_ITEM(WAIT_RESP, 'D', NULL, DROP_SEQ),
    FSM_CHR_ITEM(IDLE, 'D', NULL, DROP_SEQ),
    FSM_CHR_RANGE_ITEM(DROP_SEQ, '0', '9', NULL, DROP_SEQ),
    FSM_CHR_RANGE_ITEM(DROP_SEQ, 'A', 'F', NULL, DROP_SEQ),
    FSM_CHR_ITEM(DROP_SEQ, '*', NULL, IDLE),
    FSM_CHR_ITEM(WAIT_RESP, 'S', &data_begin, DATA_SEQ),
    FSM_CHR_ITEM(WAIT_RESP, 'R', &data_begin, DATA_SEQ),
    FSM_CHR_ITEM(WAIT_RESP, 'r', &data_begin, DATA_SEQ),
    FSM_CHR_ITEM(IDLE, 'r', &data_begin, DATA_SEQ),
    FSM_CHR_ITEM(WAIT_RESP, 'I', &data_begin, DATA_SEQ),
    FSM_CHR_ITEM(WAIT_RESP, 'i', &data_begin, DATA_SEQ),
    FSM_CHR_ITEM(IDLE, 'i', &data_begin, DATA_SEQ),
    FSM_CHR_ITEM(WAIT_RESP, 'E', NULL, WAIT_LAST),
    //
    FSM_CHR_ITEM(WAIT_RESP, 'K', NULL, KONFIG),
    FSM_STR_ITEM(KONFIG, "ONFIGURATION", NULL, KONFIG),
    FSM_CHR_ITEM(KONFIG, '_', NULL, KONFIG_N),
    FSM_CHR_RANGE_ITEM(KONFIG_N, '1', '8', &config_num, WAIT_LAST),
    FSM_CHR_ITEM(WAIT_LAST, '*', &config_wait, IDLE),
    //
    FSM_CHR_ITEM(WAIT_RESP, 'Q', NULL, WAIT_LAST),    // reboot
    //
    FSM_CHR_ITEM(WAIT_RESP, 'V', NULL, VERBOSE_SEQ),
    FSM_CHR_ITEM(WAIT_RESP, 'M', NULL, SAMPLINGMODE_SEQ),
    FSM_CHR_RANGE_ITEM(VERBOSE_SEQ, '0', '1', NULL, WAIT_LAST),
    FSM_CHR_RANGE_ITEM(SAMPLINGMODE_SEQ, '0', '1', NULL, WAIT_LAST),
    //
    FSM_CHR_ITEM(WAIT_RESP, '?', &version_read, VERSION_SEQ),
    FSM_CHR_RANGE_ITEM(VERSION_SEQ, '.', 'z', &version_read, VERSION_SEQ),
    FSM_CHR_ITEM(VERSION_SEQ, '*', &version_read, IDLE),
    FSM_CHR_RANGE_ITEM(IDLE, '0', '9', NULL, IDLE),
    FSM_CHR_ITEM(IDLE, '*', NULL, IDLE),
    //
    FSM_CHR_ITEM(ANY, '!', NULL, WAIT_LAST),
};

const size_t Context::cfsmdef(COUNT_OF(Context::fsmdef));

bool Context::push(char ch)
{
    if (trace_point == COUNT_OF(trace_buff)) trace_point = 0;
    trace_buff[trace_point++] = ch;

    for (size_t i = 0; i < cfsmdef; i++) {
        if (fsmdef[i].current == state || fsmdef[i].current == ANY) {
            if (fsmdef[i].seq)
            {
                if (fsmdef[i].offset_s <= offset && fsmdef[i].offset_e > offset)
                {
                    next_state(fsmdef[i], ch);
                    return true;
                }
            }
            else
            {
                if (fsmdef[i].ch_s <= ch && fsmdef[i].ch_e >= ch)
                {
                    next_state(fsmdef[i], ch);
                    return true;
                }
            }
        }
    }
#ifdef _DEBUG
    if (trace_point < TRACE_SIZE)
    {
        for (int i = COUNT_OF(trace_buff) - TRACE_SIZE; i < COUNT_OF(trace_buff); i++)
        {
            ATLTRACE("%c ", trace_buff[i]);
        }
    }
    for (int i = (trace_point < TRACE_SIZE) ? 0 : trace_point - TRACE_SIZE; i < trace_point; i++)
    {
        ATLTRACE("%c ", trace_buff[i]);
    }
    ATLTRACE(_T("\n"));
#endif
    return false;
}

void Context::next_state(fsm_t& t, char ch)
{
    if (t.fun) 
    {
        (this->*(t.fun))(ch);
    }
    if (state != t.next)
    {
        offset = 0;
        state = t.next;
    }
    else
    {
        offset++;
    }
}
