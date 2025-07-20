#include "StartGamePacket.hpp"
static void writeSettings(StartGamePacket& packet, BinaryStream& stream)
{
    stream.writeUnsignedLong(packet.settings.seed);
    
    stream.writeShort(packet.settings.spawnSettings.type);
    stream.writeString<Endianness::NetworkEndian>(packet.settings.spawnSettings.userDefinedBiomeName);
    stream.writeSignedVarInt(packet.settings.spawnSettings.dimension);

    stream.writeSignedVarInt(static_cast<int>(packet.settings.generatorType));
    stream.writeSignedVarInt(static_cast<int>(packet.settings.gameType));
    stream.writeBoolean(packet.settings.isHardcode);
    stream.writeSignedVarInt(static_cast<int>(packet.settings.difficulty));
    stream.writeNetworkBlockPosition(packet.settings.defaultSpawnBlock);
    stream.writeBoolean(packet.settings.achievementsDisabled);
    stream.writeSignedVarInt(packet.settings.editorWorldType);
    stream.writeBoolean(packet.settings.isCreatedInEditor);
    stream.writeBoolean(packet.settings.isExportedFromEditor);
    stream.writeSignedVarInt(packet.settings.dayCycleStopTime);
    stream.writeSignedVarInt(packet.settings.educationEditionOffer);
    stream.writeBoolean(packet.settings.educationFeatures);
    stream.writeString<Endianness::NetworkEndian>(packet.settings.educationProductId);
    stream.writeUnsignedInt(static_cast<uint32_t>(packet.settings.rainLevel));
    stream.writeUnsignedInt(static_cast<uint32_t>(packet.settings.lightningLevel));
    stream.writeBoolean(packet.settings.platformLockedContent);
    stream.writeBoolean(packet.settings.multiplayerEnabled);
    stream.writeBoolean(packet.settings.lanBroadcasting);
    stream.writeSignedVarInt(packet.settings.xboxBroadcastSettings);
    stream.writeSignedVarInt(packet.settings.platformBroadcastSettings);
    stream.writeBoolean(packet.settings.commandsEnabled);
    stream.writeBoolean(packet.settings.texturepacksRequired);

    stream.writeUnsignedVarInt(0); // Game rules
    /*stream.writeUnsignedVarInt(static_cast<uint32_t>(packet.settings.gameRules.size()));
    for (auto& entry : packet.settings.gameRules)
    {
        stream.writeString<Endianness::NetworkEndian>(entry->getName());
        stream.writeBoolean(entry->allowUseInCommand());
        stream.writeUnsignedVarInt(static_cast<uint32_t>(entry->getType()));
        if (entry->getType() == GameRule::Type::Bool)
        {
            stream.writeBoolean(entry->getValue<bool>());
        }
        else if (entry->getType() == GameRule::Type::Int)
        {
            stream.writeUnsignedVarInt(static_cast<uint32_t>(entry->getValue<int>()));
        }
        else if (entry->getType() == GameRule::Type::Float)
        {
            stream.writeUnsignedInt(static_cast<uint32_t>(entry->getValue<float>()));
        };
    };*/

    stream.writeUnsignedInt(static_cast<uint32_t>(packet.settings.experiments.list.size()));
    for (const Experiment& entry : packet.settings.experiments.list)
    {
        stream.writeString<Endianness::NetworkEndian>(entry.toggleName);
        stream.writeBoolean(entry.enabled);
    };
    stream.writeBoolean(packet.settings.experiments.experimentsEverEnabled);

    stream.writeBoolean(packet.settings.bonusChestEnabled);
    stream.writeBoolean(packet.settings.startWithMap);
    stream.writeSignedVarInt(static_cast<int>(packet.settings.playerPermissions));
    stream.writeInt(packet.settings.serverTickRange);
    stream.writeBoolean(packet.settings.hasLockedBehaviorPack);
    stream.writeBoolean(packet.settings.hasLockedResourcePack);
    stream.writeBoolean(packet.settings.isFromLockedTemplate);
    stream.writeBoolean(packet.settings.msaGamertagsOnly);
    stream.writeBoolean(packet.settings.createdFromTemplate);
    stream.writeBoolean(packet.settings.isTemplateWithLockedSettings);
    stream.writeBoolean(packet.settings.onlySpawnV1Villagers);
    stream.writeBoolean(packet.settings.personaDisabled);
    stream.writeBoolean(packet.settings.customSkinsDisabled);
    stream.writeBoolean(packet.settings.emoteChatMuted);
    stream.writeString<Endianness::NetworkEndian>(packet.settings.baseGameVersion);
    stream.writeInt(packet.settings.limitedWorldWidth);
    stream.writeInt(packet.settings.limitedWorldDepth);
    stream.writeBoolean(packet.settings.newNether);
    stream.writeString<Endianness::NetworkEndian>(packet.settings.eduSharedUriResource.buttonName);
    stream.writeString<Endianness::NetworkEndian>(packet.settings.eduSharedUriResource.linkUri);
    stream.writeBoolean(packet.settings.overrideForceExperimentalGameplay);
    stream.writeByte(packet.settings.chatRestrictionLevel);
    stream.writeBoolean(packet.settings.disablePlayerInteractions);

    stream.writeString<Endianness::NetworkEndian>(packet.settings.serverId);
    stream.writeString<Endianness::NetworkEndian>(packet.settings.worldId);
    stream.writeString<Endianness::NetworkEndian>(packet.settings.scenarioId);
};

void StartGamePacket::read(BinaryStream& stream)
{
    
};

void StartGamePacket::write(BinaryStream& stream)
{
    stream.writeSignedVarLong(this->targetActorId);
    stream.writeSignedVarLong(this->targetRuntimeId);
    stream.writeSignedVarInt(static_cast<int>(this->actorGameType));

    stream.writeVec3(this->position);
    stream.writeVec2(this->rotation.x, this->rotation.y);

    writeSettings(*this, stream); // Level Settings

    stream.writeString<Endianness::NetworkEndian>(this->levelId);
    stream.writeString<Endianness::NetworkEndian>(this->levelName);
    stream.writeString<Endianness::NetworkEndian>(this->templateContentIdentity);
    stream.writeBoolean(this->isTrial);

    stream.writeSignedVarInt(this->movementSettings.authorityMode);
    stream.writeSignedVarInt(this->movementSettings.rewindHistorySize);
    stream.writeBoolean(this->movementSettings.serverAuthoratativeBlockBreaking);

    stream.writeUnsignedLong(this->currentLevelTime);
    stream.writeSignedVarInt(this->enchantmentSeed);

    //const auto& blocks = BlockRegistry::getAll();
    std::vector<Block> blocks;
    stream.writeUnsignedVarInt(static_cast<uint32_t>(blocks.size()));
    for (const auto& block : blocks)
    {
        stream.writeString<Endianness::NetworkEndian>(block.getIdentifier());

        Nbt::CompoundTag root;
        root.add("molangVersion", Nbt::IntTag(static_cast<int32_t>(MolangVersion::BeforeVersioning)));

        {
            Nbt::CompoundTag vanillaData;
            vanillaData.add("block_id", Nbt::IntTag(block.getNetworkId()));
            root.add("vanilla_block_data", vanillaData);
        };

        {
            Nbt::CompoundTag menuCategory;
            menuCategory.add("category", Nbt::StringTag("construction"));
            //menuCategory.add("group", Nbt::StringTag(""));
            root.add("menu_category", menuCategory);
        };

        {
            Nbt::ListTag properties{ {}, Nbt::TagType::Compound };
            for (auto& [key, value] : block.getStates())
            {
                Nbt::CompoundTag stateTag;
                stateTag.add("name", Nbt::StringTag(key));

                Nbt::ListTag states;
                for (StateType& state : value.getPossibleStates())
                {
                    const int type = value.type();
                    if (type == 0)
                    {
                        Nbt::StringTag tag{ std::get<std::string>(state) };
                        states.emplace_back(tag);
                    }
                    else if (type == 1)
                    {
                        Nbt::IntTag tag{ std::get<int>(state) };
                        states.emplace_back(tag);
                    }
                    else {
                        Nbt::ByteTag tag{ std::get<bool>(state) };
                        states.emplace_back(tag);
                    };
                };

                stateTag.add("enum", states);
            };
            root.add("properties", properties);
        };

        {
            Nbt::ListTag properties{ {}, Nbt::TagType::Compound };
            root.add("permutations", properties);
        };

        Nbt::write<Endianness::NetworkEndian>(stream, root.copy(), true);
    };

    stream.writeString<Endianness::NetworkEndian>(this->multiplayerCorrelationId);
    stream.writeBoolean(this->enableItemStackNetManager);
    stream.writeString<Endianness::NetworkEndian>(this->serverVersion);

    Nbt::write<Endianness::NetworkEndian>(stream, this->playerPropertyData.copy(), true);

    stream.writeUnsignedLong(this->serverBlockTypeRegistryChecksum);
    stream.writeUUID(this->worldTemplateId);
    stream.writeBoolean(this->clientSideGeneration);
    stream.writeBoolean(this->blockNetworkIdsAreHashes);

    stream.writeBoolean(this->networkPermissions.serverAuthSoundEnabled);
};