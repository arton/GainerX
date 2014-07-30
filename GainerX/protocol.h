#if !defined(_GAINER_PROTOCOL_H)
#define _GAINER_PROTOCOL_H

#include "interthread.h"

enum State {
    IDLE,
    WAIT_RESP,
    WAIT_LAST,
    //
    BTN_P,
    BTN_R,
    DATA_SEQ,
    DROP_SEQ,
    VERSION_SEQ,
    VERBOSE_SEQ,
    SAMPLINGMODE_SEQ,
    KONFIG,
    KONFIG_N,
    //
    ANY
};

const int MAX_RESPONSE = 64;
const int MODE_CHANGE_INTERVAL = 200;
const size_t TRACE_SIZE = 32;

struct Context {
    typedef void (Context::*fsmfn_t)(char);

    struct fsm_t {
        State current;
        const char* seq;
        int offset_s;
        int offset_e;
        char ch_s;   // valid if seq == NULL
        char ch_e;
        fsmfn_t fun;
        State next;
    };
#define FSM_STR_ITEM(c,s,fn,n) { c, s, 0, strlen(s), 0, 0, fn, n }
#define FSM_CHR_ITEM(c, s, fn, n) { c, NULL, 0, 0, s, s, fn, n }
#define FSM_CHR_RANGE_ITEM(c, s, e, fn, n) { c, NULL, 0, 0, s, e, fn, n }

    static fsm_t fsmdef[];
    static const size_t cfsmdef;

    Context(ThreadParam& param) : tparam(param), offset(0), state(IDLE), trace_point(0)
    {
    }
    inline State current_state() { return state; }
    inline bool is_idle() { return state == IDLE; }
    inline void notify(WPARAM wp = 0, LPARAM lp = 0)
    {
        to_controller(WM_COM_RESPONSE, wp, lp);
    }
    inline void notify_reboot()
    {
        to_controller(WM_COM_REBOOT, 0, 0);
    }
    inline void text_notify()
    {
        if (iswlower(*(LPCTSTR)bstr) && lastNotify == (LPCTSTR)bstr) return;
        lastNotify = (LPCTSTR)bstr;
        if (tparam.hWnd)
        {
            ::PostMessage(tparam.hWnd, WM_COM_READRESULT, 0, (LPARAM)bstr.Copy());
        }
        else
        {
            ::PostThreadMessage(tparam.threadId, WM_COM_READRESULT, 0, (LPARAM)bstr.Copy());
        }
    }
    inline void next_state(State n)
    { 
        if (state != n) {
            offset = 0;
            state = n; 
        }
    }
    bool push(char ch);
    void next_state(fsm_t& t, char ch);
    //
private:
    ThreadParam& tparam;
    int number;
    int value;
    CComBSTR bstr;
    CComBSTR lastNotify;
    //
    inline void to_controller(UINT msg, WPARAM wp, LPARAM lp)
    {
        if (tparam.hWnd)
        {
            ::PostMessage(tparam.hWnd, msg, wp, lp);
        }
        else
        {
            ::PostThreadMessage(tparam.threadId, msg, wp, lp);
        }
    }
    //
    State state;
    int offset;
    //
    char trace_buff[TRACE_SIZE * 2];
    int trace_point;
    //
    void button_released(char ch)
    {
        notify(BUTTON_RELEASED);
    }
    void button_pressed(char ch)
    {
        notify(BUTTON_PRESSED);
    }
    void config_num(char ch)
    {
    }
    void config_wait(char ch)
    {
        Sleep(MODE_CHANGE_INTERVAL);
    }
    void version_read(char ch)
    {
        if (ch == '?')
        {
            bstr.Empty();
        }
        else if (ch == '*')
        {
            text_notify();
        }
        else
        {
            bstr.Append(ch);
        }
    }
    void data_begin(char ch)
    {
        bstr.Empty();
        bstr.Append(ch);
    }
    void data_seq(char ch)
    {
        bstr.Append(ch);
    }
    void data_end(char ch)
    {
        text_notify();
    }
    //
};


#endif
