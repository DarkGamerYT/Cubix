#include "StartGamePacket.hpp"
void StartGamePacket::read(BinaryStream& stream)
{

};

void StartGamePacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorUniqueId>::write(this->actorUniqueId, stream);
    BinaryStream::serialize<ActorRuntimeId>::write(this->actorRuntimeId, stream);
    stream.writeSignedVarInt(static_cast<int>(this->actorGameType));

    stream.writeVec3(this->position);
    stream.writeVec2(this->rotation);

    BinaryStream::serialize<LevelSettings>::write(*this->levelSettings, stream);

    stream.writeString<Endianness::NetworkEndian>(this->levelId);
    stream.writeString<Endianness::NetworkEndian>(this->levelName);
    stream.writeString<Endianness::NetworkEndian>(this->templateContentIdentity.toString());
    stream.writeBoolean(this->isTrial);

    // Movement settings
    stream.writeSignedVarInt(this->movementSettings.rewindHistorySize);
    stream.writeBoolean(this->movementSettings.serverAuthoratativeBlockBreaking);

    stream.writeUnsignedLong(this->tick);
    stream.writeSignedVarInt(this->enchantmentSeed);

    const auto& blocks = BlockRegistry::getAll();
    stream.writeUnsignedVarInt(static_cast<uint32_t>(blocks.size()));
    for (const auto& block : blocks)
    {
        stream.writeString<Endianness::NetworkEndian>(block->getIdentifier());

        Nbt::CompoundTag root;
        root.add("molangVersion", Nbt::IntTag(static_cast<int32_t>(MolangVersion::BeforeVersioning)));

        {
            Nbt::CompoundTag vanillaData;
            vanillaData.add("block_id", Nbt::IntTag(block->getNetworkId()));
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
            for (auto& [key, value] : block->getStates())
            {
                Nbt::CompoundTag stateTag;
                stateTag.add("name", Nbt::StringTag(key));

                Nbt::ListTag states;
                for (const StateType& state : value.getPossibleStates())
                {
                    switch (value.type())
                    {
                        case 0: {
                            Nbt::StringTag tag{ std::get<std::string>(state) };
                            states.emplace_back(tag);
                            break;
                        };
                        case 1: {
                            Nbt::IntTag tag{ std::get<int>(state) };
                            states.emplace_back(tag);
                            break;
                        };
                        default: {
                            Nbt::ByteTag tag{ std::get<bool>(state) };
                            states.emplace_back(tag);
                            break;
                        };
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
    stream.writeBoolean(this->tickDeathSystemsEnabled);
    stream.writeBoolean(this->networkPermissions.serverAuthSoundEnabled);
};