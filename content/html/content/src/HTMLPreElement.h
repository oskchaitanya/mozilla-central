/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_HTMLPreElement_h
#define mozilla_dom_HTMLPreElement_h

#include "mozilla/Util.h"

#include "nsIDOMHTMLPreElement.h"
#include "nsGenericHTMLElement.h"

namespace mozilla {
namespace dom {

class HTMLPreElement : public nsGenericHTMLElement,
                       public nsIDOMHTMLPreElement
{
public:
  HTMLPreElement(already_AddRefed<nsINodeInfo> aNodeInfo)
    : nsGenericHTMLElement(aNodeInfo)
  {
    SetIsDOMBinding();
  }
  virtual ~HTMLPreElement();

  // nsISupports
  NS_DECL_ISUPPORTS_INHERITED

  // nsIDOMNode
  NS_FORWARD_NSIDOMNODE_TO_NSINODE

  // nsIDOMElement
  NS_FORWARD_NSIDOMELEMENT_TO_GENERIC

  // nsIDOMHTMLElement
  NS_FORWARD_NSIDOMHTMLELEMENT_TO_GENERIC

  // nsIDOMHTMLPreElement
  NS_IMETHOD GetWidth(int32_t* aWidth);
  NS_IMETHOD SetWidth(int32_t aWidth);

  virtual bool ParseAttribute(int32_t aNamespaceID,
                                nsIAtom* aAttribute,
                                const nsAString& aValue,
                                nsAttrValue& aResult);
  NS_IMETHOD_(bool) IsAttributeMapped(const nsIAtom* aAttribute) const;
  virtual nsMapRuleToAttributesFunc GetAttributeMappingFunction() const;

  virtual nsresult Clone(nsINodeInfo *aNodeInfo, nsINode **aResult) const;

  virtual nsIDOMNode* AsDOMNode() { return this; }

  // WebIDL API
  int32_t Width() const
  {
    return GetIntAttr(nsGkAtoms::width, 0);
  }
  void SetWidth(int32_t aWidth, mozilla::ErrorResult& rv)
  {
    rv = SetIntAttr(nsGkAtoms::width, aWidth);
  }

protected:
  virtual JSObject* WrapNode(JSContext *aCx, JSObject *aScope,
                             bool *aTriedToWrap) MOZ_OVERRIDE;
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_HTMLPreElement_h
