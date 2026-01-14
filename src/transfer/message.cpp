#include <string>

// Protocol format:
//
// REQ <filename> <filesize>\n
// MSG <optional message>\n
// END\n
//
// Response:
// ACC
// REJ
