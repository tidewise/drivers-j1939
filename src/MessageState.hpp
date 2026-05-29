#ifndef J1939_MESSAGE_STATE_HPP
#define J1939_MESSAGE_STATE_HPP

namespace j1939 {
    enum MessageState {
        /** Message PGN is not recognized or is not supported by this handler */
        UNKNOWN_PGN,
        /** Transport Protocol Data Transfer message has invalid sequence number */
        INVALID_SEQUENCE_NUMBER,
        /** Transport Protocol Data Transfer segment arrived and was processed */
        PROCESSED,
        /** Message is complete and ready for processing */
        COMPLETE
    };
}

#endif