/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "nsTraversal.h"

#include "nsIDOMNode.h"
#include "nsIDOMNodeFilter.h"
#include "nsError.h"
#include "nsINode.h"
#include "mozilla/dom/NodeFilterBinding.h"
#include "mozilla/AutoRestore.h"

#include "nsGkAtoms.h"

using namespace mozilla;
using namespace mozilla::dom;

nsTraversal::nsTraversal(nsINode *aRoot,
                         uint32_t aWhatToShow,
                         const NodeFilterHolder &aFilter) :
    mRoot(aRoot),
    mWhatToShow(aWhatToShow),
    mFilter(aFilter),
    mInAcceptNode(false)
{
    NS_ASSERTION(aRoot, "invalid root in call to nsTraversal constructor");
}

nsTraversal::~nsTraversal()
{
    /* destructor code */
}

/*
 * Tests if and how a node should be filtered. Uses mWhatToShow and
 * mFilter to test the node.
 * @param aNode     Node to test
 * @param _filtered Returned filtervalue. See nsIDOMNodeFilter.idl
 * @returns         Errorcode
 */
nsresult nsTraversal::TestNode(nsINode* aNode, int16_t* _filtered)
{
    NS_ENSURE_TRUE(!mInAcceptNode, NS_ERROR_DOM_INVALID_STATE_ERR);

    *_filtered = nsIDOMNodeFilter::FILTER_SKIP;

    uint16_t nodeType = aNode->NodeType();

    if (nodeType <= 12 && !((1 << (nodeType-1)) & mWhatToShow)) {
        return NS_OK;
    }

    if (!mFilter.GetISupports()) {
        // No filter, just accept
        *_filtered = nsIDOMNodeFilter::FILTER_ACCEPT;
        return NS_OK;
    }

    if (mFilter.HasWebIDLCallback()) {
        AutoRestore<bool> inAcceptNode(mInAcceptNode);
        mInAcceptNode = true;
        ErrorResult res;
        *_filtered = mFilter.GetWebIDLCallback()->AcceptNode(*aNode, res);
        return res.ErrorCode();
    }

    nsCOMPtr<nsIDOMNode> domNode = do_QueryInterface(aNode);
    AutoRestore<bool> inAcceptNode(mInAcceptNode);
    mInAcceptNode = true;
    return mFilter.GetXPCOMCallback()->AcceptNode(domNode, _filtered);
}
