// ControlFlowFlattening.cpp

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct ControlFlowFlattening : public FunctionPass {
    static char ID;
    ControlFlowFlattening() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      bool changed = false;

      // Iterate over all basic blocks in the function
      for (auto &BB : F) {
        // Iterate over all instructions in the basic block
        for (auto &I : BB) {
          // If the instruction is a branch instruction
          if (auto *BI = dyn_cast<BranchInst>(&I)) {
            // If the branch instruction is not unconditional
            if (!BI->isUnconditional()) {
              // Create a new basic block for the branch target
              BasicBlock *newBB = BasicBlock::Create(BB.getContext(), "", &F);

              // Move all instructions from the branch target to the new basic block
              for (auto &I : *BI->getSuccessor(0)) {
                I.removeFromParent();
                newBB->getInstList().push_back(&I);
              }

              // Update the branch instruction to jump to the new basic block
              BI->setSuccessor(0, newBB);

              changed = true;
            }
          }
        }
      }

      return changed;
    }
  };
}

char ControlFlowFlattening::ID = 0;

static RegisterPass<ControlFlowFlattening> X("flatten-cf", "Control Flow Flattening");

