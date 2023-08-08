//******************************************************************************
// Copyright (C) 1999 Jim Wanner and the SourceMonitor team.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//******************************************************************************

#pragma once

#include <stdbool.h>
#include "smstring.h"

namespace smos
{
    namespace smcore
    {
        class Languages
        {
        public:
            /**
             * @brief Definition of enums according to the strings in the body
             *
             */
            enum class Type
            {
                SMC = 0,
                SMCPP = 1,
                SMCS = 2,
                SMDELPHI = 3,
                SMHTML = 4,
                SMJAVA = 5,
                SMVBNET = 6,
                SMVISUALBASIC = 7
            };

            /**
             * @brief Convert the enum to a char* as in the array languageStrings
             * @see languageStrings
             *
             * @param smos::smcore::Languages::Type Kind of language to get string for
             * @return const char* Language enum as string
             */
            static const char *getLanguageString(smos::smcore::Languages::Type lang);

            /**
             * @brief Validate the given string if it matches the given class type (enum)
             * @see https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s14.html
             * @param classString Class as string like SMCpp
             * @param classType Class as enum type
             * @return bool Result of case insensitive comparison
             */
            static bool isClassOfType(smos::smcore::SMString classString, smos::smcore::Languages::Type classType);

            /**
             * @brief Array of language strings, order equal to the enum here
             */
            static const char *languageStrings[];

        protected:
            /**
             * @brief Function to compare two characters case insensitive
             * @see https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s14.html
             * @param a Left character
             * @param b Right character
             * @return bool Result of case insensitive comparison
             */
            static bool Languages::caseInsCharCompareN(char a, char b);
        };
    }
}
