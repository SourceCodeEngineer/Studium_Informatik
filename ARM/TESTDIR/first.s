
//
// hello.s: hello world in ARM assembler
//
// How to compile:
//
//     as    -o  hello.o   hello.s
//     gcc   -o  hello     hello.o
//

        .global main

// ************************ Starting variable definition *****************
        .data
// ***********************************************************************

HelloStr:                               // Label marking this location in memory
        .asciz "Hello Innsbruck\n"      // ASCII codes for the string


// ************************ Starting computer instruction ****************
        .text
// ***********************************************************************
main:
        push    {lr}                    // Save the return address on the stack
        push    {fp}                    // Save the frame pointer on the stack
                                        // Explained later in CS255

        /* ----------------------------------------
           Pass the string to printf function
           ---------------------------------------- */
        movw    r0, #:lower16:HelloStr
        movt    r0, #:upper16:HelloStr

        /* ----------------------------------------
           Call the printf function
           ---------------------------------------- */
        bl      printf                  // Call printf function with input string     

        pop     {fp}                    // Pop the frame pointer
        pop     {pc}                    // Pop the return address into PC
                                        // Explained later in CS255
        .end

Any text that follws ".end" is ignored (treated as comment)
