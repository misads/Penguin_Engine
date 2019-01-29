#pragma once

#define _TRY(operation,errorstring,fatal) if(!operation)_ERROR(TEXT(errorstring),(fatal));