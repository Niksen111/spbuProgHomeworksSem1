#pragma once

// Error codes:
// -1  --  impossible to allocate memory


// Converts an expression from the infix form to the postfix form
char* convertToPostfixForm(const char infix[], int* errorCode);