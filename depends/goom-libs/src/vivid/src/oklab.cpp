//
// Copyright (c) 2020 Björn Ottosson
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// c.f. https://bottosson.github.io/posts/oklab/
//

#include "vivid/conversion.h"

namespace vivid::oklab {


////////////////////////////////////////////////////////////////////////////////
oklab_t fromSrgb( const srgb_t& srgb ) {
    return oklab::fromLrgb( lrgb::fromSrgb( srgb ) );
}


////////////////////////////////////////////////////////////////////////////////
oklab_t fromLrgb( const lrgb_t& lrgb )
{
    const float l = 0.4122214708f * lrgb.x + 0.5363325363f * lrgb.y + 0.0514459929f * lrgb.z;
	const float m = 0.2119034982f * lrgb.x + 0.6806995451f * lrgb.y + 0.1073969566f * lrgb.z;
	const float s = 0.0883024619f * lrgb.x + 0.2817188376f * lrgb.y + 0.6299787005f * lrgb.z;

    const float l_ = std::cbrtf( l );
    const float m_ = std::cbrtf( m );
    const float s_ = std::cbrtf( s );

    return {
        0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_,
        1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_,
        0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_,
    };
}


}   //  ::vivid::oklab