#!/bin/zsh

QT_PATH="/Users/$USER/Qt/6.10.2/macos"

if [ ! -d "$QT_PATH" ]; then
    echo "Failed to find $QT_PATH"
    echo "Please adjust QT_PATH in setup_qt.sh"
    exit 1
fi

EXPORT_STR="export CMAKE_PREFIX_PATH=\"$QT_PATH::\${CMAKE_PREFIX_PATH}\""

if grep -qF "$QT_PATH" ~/.zshrc; then
    echo "CMAKE_PREFIX_PATH already set in ~/.zshrc"
else
    echo "$EXPORT_STR" >> ~/.zshrc
    echo "Added CMAKE_PREFIX_PATH to ~/.zshrc"
fi