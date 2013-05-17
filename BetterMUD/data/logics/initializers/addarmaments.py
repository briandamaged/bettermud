import BetterMUD

def init():
    mud = BetterMUD.GameWrap()

    # add arms to every item
    mud.BeginItem()
    while mud.IsValidItem():
        item = BetterMUD.item( mud.CurrentItem() )
        template = BetterMUD.itemtemplate( item.TemplateID() )
        if not item.HasAttribute( "arms" ):
            item.AddAttribute( "arms", template.GetAttribute( "arms" ) )
        mud.NextItem()

    # add defaultweapon and weapon to every character
    mud.BeginCharacter()
    while mud.IsValidCharacter():
        character = BetterMUD.character( mud.CurrentCharacter() )
        template = BetterMUD.charactertemplate( character.TemplateID() )
        if not character.HasAttribute( "defaultweapon" ):
            character.AddAttribute( "defaultweapon", template.GetAttribute( "defaultweapon" ) )
        if not character.HasAttribute( "weapon" ):
            character.AddAttribute( "weapon", template.GetAttribute( "weapon" ) )
        mud.NextCharacter()