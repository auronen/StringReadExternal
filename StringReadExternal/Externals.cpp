// Supported with union (c) 2020 Union team
// Union SOURCE file



namespace GOTHIC_ENGINE {
    


    int STR_GetSpellName()
    {
        int index;
        static zSTRING output;
        zCPar_Symbol* sym = NULL;

        parser->GetParameter(index);

        sym = parser->GetSymbol("TXT_SPELLS");

        if (sym) // if the symbol exists
        {
            sym->GetValue(output, index);
            parser->SetReturn(output);
        }

        return FALSE;
    }

    // Registers the external functions
    // Has to be called from Plugin.cpp - Game_DefineExternals()
    void Plugin_DefineExternals() {
        // DefineExternal(   [Daedalus func name], [C++ func implemenatation],    [return type], [input types](n),       [last one is always zPAR_TYPE_VOID]  )
        parser->DefineExternal("STR_GetSpellName",           STR_GetSpellName, zPAR_TYPE_STRING,    zPAR_TYPE_INT,        zPAR_TYPE_VOID);
    }
}