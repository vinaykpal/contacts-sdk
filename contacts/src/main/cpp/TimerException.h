//
// Timer exception class
//

#ifndef MYAPPLICATION_TIMEREXCEPTION_H
#define MYAPPLICATION_TIMEREXCEPTION_H
#include<string>
namespace contacts {
/**
 *   Signals a problem with the execution of a Timer call.
 */

    class CTimerException : public std::exception {
    public:
        /**
       *   Construct a SharedMemoryException with a explanatory message.
       *   @param message explanatory message
       *   @param bSysMsg true if system message (from strerror(errno))
       *   should be postfixed to the user provided message
       */
        CTimerException(const std::string &message, bool bSysMsg = false) throw();


        /** Destructor.
         * Virtual to allow for subclassing.
         */
        virtual ~CTimerException() throw();

        /** Returns a pointer to the (constant) error description.
         *  @return A pointer to a \c const \c char*. The underlying memory
         *          is in posession of the \c Exception object. Callers \a must
         *          not attempt to free the memory.
         */
        virtual const char *what() const throw() { return m_sMsg.c_str(); }

    protected:
        /** Error message.
         */
        std::string m_sMsg;
    };

    CTimerException::CTimerException(const std::string &sMessage, bool blSysMsg /*= false*/ ) throw()
            : m_sMsg(sMessage) {
        if (blSysMsg) {
            m_sMsg.append(": ");
            //m_sMsg.append(strerror(errno));
        }
    }

    CTimerException::~CTimerException() throw() {

    }
}
#endif //MYAPPLICATION_TIMEREXCEPTION_H
