/*
    Copyright (c) 2002-2021 Tampere University.

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
 * @file BlocksModel.cc
 *
 * Implementation of the Blocks utility class which contains a Blocks model.
 *
 * @author Maarten Molendijk 2020 (m.j.molendijk@tue.nl)
 * @author Kanishkan Vadivel 2021 (k.vadivel@tue.nl)
 */

#include "BlocksModel.hh"

#include <exception>
#include <iostream>

using namespace tinyxml2;
using namespace std;

/**
 * Load and parse the Blocks 'architecture.xml'.
 */
void
BlocksModel::LoadModelFromXml() {
    // TODO(mm): add check for configuration bits
    if (!VerifyXmlStructure()) return;

    XMLElement* currentElement = mDoc.FirstChildElement("architecture")
                                     ->FirstChildElement("configuration")
                                     ->FirstChildElement("functionalunits")
                                     ->FirstChildElement();
    XMLElement* srcElement;
    bool allParsed = false;
    while (!allParsed) {
        FunctionalUnit unit = {};
        unit.usesOut0 = false;
        unit.usesOut1 = false;
        string unitTypeString = currentElement->Attribute("type");
        unit.type = stringToEnum.at(unitTypeString);
        unit.name = currentElement->Attribute("name");
        srcElement = currentElement
                         ->FirstChildElement();  // Descend one level in the
                                                 // DOM to find the functional
                                                 // units properties
        for (int srcnum = 0; srcnum <= 4; srcnum++) {
            unit.src.push_back(srcElement->Attribute("source"));
            srcElement = srcElement->NextSiblingElement();
            if (srcElement == NULL) {
                break;
            } else if (srcElement != NULL && srcnum == 3) {
                // If this is the case, there are to many input connections to
                // a single FU
                cerr << "Too many connections to <" << unitTypeString << "> "
                     << unit.name << " (and possibly more)." << endl;
                cerr << "Aborting translation, please make sure each FU "
                        "contains <= 4 inputs."
                     << endl;
                return;
            }
        }

        mFunctionalUnitList.push_back(unit);  // Add functional unit to list
        currentElement =
            currentElement
                ->NextSiblingElement();  // Navigate to next functional unit
        if (currentElement == NULL) allParsed = true;
    }
}

/**
 * Verify the structure of the 'architecture.xml' file.
 */
bool
BlocksModel::VerifyXmlStructure() {
    XMLElement* archElement = mDoc.FirstChildElement("architecture");
    if (archElement == NULL) {
        fprintf(
            stderr,
            "Error reading XML file, could not find <architecture> "
            "element.\n");
        return false;
    }
    XMLElement* configElement =
        archElement->FirstChildElement("configuration");
    if (configElement == NULL) {
        fprintf(
            stderr,
            "Error reading XML file, could not find <configuration> "
            "element.\n");
        return false;
    }
    XMLElement* fuElement =
        configElement->FirstChildElement("functionalunits");
    if (fuElement == NULL) {
        fprintf(
            stderr,
            "Error reading XML file, could not find <functionalunits> "
            "element.\n");
        return false;
    }
    return true;
}
