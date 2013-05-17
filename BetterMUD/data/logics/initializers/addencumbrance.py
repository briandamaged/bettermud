import BetterMUD

def init():
    mud = BetterMUD.GameWrap()

    # add weight to every item
    mud.BeginItem()
    while mud.IsValidItem():
        item = BetterMUD.item( mud.CurrentItem() )
        template = BetterMUD.itemtemplate( item.TemplateID() )
        if not item.HasAttribute( "weight" ):
            item.AddAttribute( "weight", template.GetAttribute( "weight" ) )
        mud.NextItem()

    # add encumbrance to every character
    mud.BeginCharacter()
    while mud.IsValidCharacter():
        character = BetterMUD.character( mud.CurrentCharacter() )
        template = BetterMUD.charactertemplate( character.TemplateID() )
        if not character.HasAttribute( "encumbrance" ):
            character.AddAttribute( "encumbrance", template.GetAttribute( "encumbrance" ) )
        if not character.HasAttribute( "maxencumbrance" ):
            character.AddAttribute( "maxencumbrance", template.GetAttribute( "maxencumbrance" ) )

        # now calculate encumbrance of carried items
        character.BeginItem()
        encumbrance = 0
        while character.IsValidItem():
            item = BetterMUD.item( character.CurrentItem() )
            if item.IsQuantity():
                encumbrance = encumbrance + item.GetAttribute( "weight" ) * item.GetQuantity()
            else:
                encumbrance = encumbrance + item.GetAttribute( "weight" )
            character.NextItem()
        character.SetAttribute( "encumbrance", encumbrance )
        if not character.HasLogic( "encumbrance" ):
            character.AddLogic( "encumbrance" )
        mud.NextCharacter()