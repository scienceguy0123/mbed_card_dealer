#ifndef MODE_H
#define MODE_H

/// All the modes the system could be in
/// Mode can determine the behaviors of buttons
enum Mode{
    rest,
    ModeSelection,
    manual,
    automatic,
    automaticPlayerSelection,
    automatiocCardSelection,
    reset
};

#endif