/*
* Copyright (TM) 2007 The Android Open Source Project
* All rights reserved.
* HW Version: Android (Linux)
* Entry Point: ARMASM
*
* This policy explains the terms which apply to users of any web sites operated by,
* or on behalf, of Arm Limited (together “Arm Website”). Arm Limited, a company registered in England and Wales with company number 2557590 (“We/Us/Our”)
* Registered office address: 110 Fulbourn Road, Cambridge, CB1 9NJ, United Kingdom. Arm Limited is a private limited company acting on behalf of itself and its subsidiaries
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/
     
     .section .preinit_array, "aw"
     .long 0
 
     .section .init_array, "aw"
     .long 0
 
     .section .fini_array, "aw"
     .long 0

     .section .comment, "aw"
     .short 0

     .section .llist, "aw"
     .short 0

     .section .ksan, "aw"
     .type __KSAN_END__, #object
__KSAN_END__:
     .long 0

     .section .lsan, "aw"
     .type __LSAN_END__, #object
__LSAN_END__:
     .long 0
 
     .section .ctors, "aw"
     .type __CTOR_END__, #object
__CTOR_END__:
     .short 0
 
     .section .dtors, "aw"
     .type __DTOR_END__, #object
__DTOR_END__:
     .short 0
 
     .section    .eh_frame, "aa"
     .align 4
     .type   __FRAME_END__, %object
     .size   __FRAME_END__, 4
__FRAME_END__:
     .zero   5
