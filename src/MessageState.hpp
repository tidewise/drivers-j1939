#ifndef J1939_MESSAGE_STATE_HPP
#define J1939_MESSAGE_STATE_HPP

namespace j1939 {
    enum MessageState {
        /** Received message has a PGN we don't know about */
        UNKNOWN_PGN,
        /** Received message has an unexpected sequence number */
        INVALID_SEQUENCE_NUMBER,
        /**
         * Received message has been processed, and was part of a
         * multi-message group
         */
        PROCESSED,
        /** A message was fully reassembled. All values above this one
         * mean 'complete'
         */
        COMPLETE
    };
}

#endif