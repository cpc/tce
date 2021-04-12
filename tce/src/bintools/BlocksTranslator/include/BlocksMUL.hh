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
 * @file BlocksMUL.hh
 *
 * Declaration of BlocksMUL Class. This class resembles a single output in the
 * Blocks architecture.
 *
 * @author Maarten Molendijk 2020 (m.j.molendijk@tue.nl)
 * @author Kanishkan Vadivel 2021 (k.vadivel@tue.nl)
 */

#ifndef BLOCKS_MUL_HH
#define BLOCKS_MUL_HH

#include "BlocksFU.hh"

class BlocksMUL : public BlocksFU {
public:
    TTAMachine::FunctionUnit* mul;
    BlocksMUL(
        TTAMachine::Machine& mach, const std::string& name,
        std::list<std::string> sources,
        std::shared_ptr<TTAMachine::Socket> in1sock,
        std::shared_ptr<TTAMachine::Socket> in2sock);
    ~BlocksMUL() {
        while (!ops.empty()) {
            delete ops.back();
            ops.pop_back();
        }
    }

private:
    void ConfigurePipeline(
        TTAMachine::ExecutionPipeline* pipeline, int numOfOperands);
    void BindPorts(TTAMachine::HWOperation* hwOp, int numOfOperands);
    TTAMachine::HWOperation* CreateHWOp(
        const std::string& name, int numOfOperands);
};

/**
 * Declaration of BlocksMULPair Class. This class is a wrapper for BlocksMUL
 * class to group two units both representing a different output of the same
 * Blocks Unit.
 */
class BlocksMULPair {
public:
    // Smart pointers for automated memory management
    std::unique_ptr<BlocksMUL> mul0;
    std::unique_ptr<BlocksMUL> mul1;
    std::shared_ptr<TTAMachine::Socket> in1sock;
    std::shared_ptr<TTAMachine::Socket> in2sock;
    std::list<std::string> sources;

    BlocksMULPair(
        TTAMachine::Machine& mach, const std::string& name,
        std::list<std::string> sources, bool usesOut0, bool usesOut1);

private:
};
#endif
