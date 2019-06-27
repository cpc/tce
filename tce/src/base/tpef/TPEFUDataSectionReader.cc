/*
    Copyright (c) 2002-2009 Tampere University.

    This file is part of TTA-Based Codesign Environment (TCE).

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
 */
/**
 * @file TPEFUDataSectionReader.cc
 *
 * Definition of TPEFUDataSectionReader class.
 *
 * @author Mikael Lepist� 2003 (tmlepist-no.spam-cs.tut.fi)
 *
 * @note rating: yellow
 */

#include "TPEFUDataSectionReader.hh"
#include "SectionReader.hh"
#include "BaseType.hh"
#include "SafePointer.hh"

#include "UDataSection.hh"

namespace TPEF {

using ReferenceManager::SafePointer;
using ReferenceManager::SectionIndexKey;
using std::string;

TPEFUDataSectionReader TPEFUDataSectionReader::proto_;

/**
 * Constructor.
 *
 * Registers itself to SectionReader.
 */
TPEFUDataSectionReader::TPEFUDataSectionReader() : TPEFSectionReader() {
    SectionReader::registerSectionReader(this);
}

/**
 * Destructor.
 */
TPEFUDataSectionReader::~TPEFUDataSectionReader() {
}

/**
 * Returns the type of section it is meant to read.
 *
 * @return The type of section it can read.
 */
Section::SectionType
TPEFUDataSectionReader::type() const {
    return Section::ST_UDATA;
}

/**
 * Reads section data from TPEF binary file.
 *
 * @param stream Stream to be read from.
 * @param section Section where the information is to be stored.
 * @exception UnreachableStream If reading of section fails.
 * @exception KeyAlreadyExists Key was in use when trying to register object.
 * @exception EndOfFile If end of file were reached while it shouldn't.
 * @exception OutOfRange Some of read values were out of range.
 * @exception WrongSubclass Some class couldn't do what it was asked for.
 * @exception UnexpectedValue If there was unexpected value when reading.
 */
void
TPEFUDataSectionReader::readData(BinaryStream& stream, Section* section) const {
    // base classes implementation must be called with these TPEF readers
    TPEFSectionReader::readData(stream, section);

    UDataSection* uDataSection = dynamic_cast<UDataSection*>(section);
    assert(uDataSection != NULL);

    // check that link section is defined properly
    assert(header().linkId == 0);

    dynamic_cast<TPEFReader*>(
        parent())->addSectionSize(section, header().bodyLength);

    uDataSection->setDataLength(header().bodyLength);
}
}
