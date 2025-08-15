#include "PlayerListPacket.hpp"
void PlayerListPacket::read(BinaryStream& stream)
{

};

void PlayerListPacket::write(BinaryStream& stream)
{
    stream.writeByte(static_cast<uint8_t>(this->action));
    switch (this->action)
    {
        case PlayerListPacket::Action::Add: {
            std::vector<bool> trustedSkins;

            stream.writeUnsignedVarInt(static_cast<uint32_t>(this->players.size()));
            for (const auto& player : this->players)
            {
                const auto& request = player->getConnection();
                stream.writeUUID(request->getSelfSignedId());
                BinaryStream::serialize<ActorUniqueId>::write(player->getUniqueId(), stream);
                stream.writeString<Endianness::NetworkEndian>(player->getDisplayName());
                stream.writeString<Endianness::NetworkEndian>(request->getXuid());
                stream.writeString<Endianness::NetworkEndian>(""); // Platform Chat Id
                stream.writeInt(request->getBuildPlatform());

                {
                    // Write skin data
                    auto& skin = player->getSkin();

                    skin.write(stream);
                    trustedSkins.emplace_back(skin.isTrusted());
                };

                stream.writeBoolean(false); // Is teacher
                stream.writeBoolean(false); // Is host
                stream.writeBoolean(player->getConnection()->isSubClient());
                stream.writeInt(Util::Color{0, 0,0, 0}.encode());
            };

            stream.writeUnsignedVarInt(static_cast<uint32_t>(trustedSkins.size()));
            for (const bool isTrusted : trustedSkins)
                stream.writeBoolean(isTrusted);
            break;
        };
        case PlayerListPacket::Action::Remove: {
            stream.writeUnsignedVarInt(static_cast<uint32_t>(this->players.size()));
            for (const auto& player : this->players)
            {
                const auto& request = player->getConnection();
                stream.writeUUID(request->getSelfSignedId());
            };
            break;
        };
    };
};