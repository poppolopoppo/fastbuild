// FileNode.h - a node that tracks a single file
//------------------------------------------------------------------------------
#pragma once

// Includes
//------------------------------------------------------------------------------
#include "Node.h"

// FileNode
//------------------------------------------------------------------------------
class FileNode : public Node
{
public:
    explicit FileNode( const AString & fileName, uint32_t controlFlags );
    virtual bool Initialize( NodeGraph & nodeGraph, const BFFIterator & funcStartIter, const Function * function ) override;
    virtual ~FileNode() override;

    static inline Node::Type GetTypeS() { return Node::FILE_NODE; }

    virtual bool IsAFile() const override { return true; }

    static void HandleWarningsMSVC( Job * job, const AString & name, const char * data, uint32_t dataSize );
    static void HandleWarningsClangGCC( Job * job, const AString & name, const char * data, uint32_t dataSize );
protected:
    friend class ObjectNode;
    virtual BuildResult DoBuild( Job * job ) override;

    enum OutputLevel : uint8_t
    {
        INFOS       = 0,
        WARNINGS    = 1,
        ERRORS      = 2,
    };

    static void DumpOutput( Job * job, const char * data, uint32_t dataSize, const AString & name, OutputLevel severity = ERRORS );

    friend class Client;
};

//------------------------------------------------------------------------------
