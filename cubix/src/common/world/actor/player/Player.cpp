#include "Player.hpp"
#include "../../../network/ServerNetworkHandler.hpp"
#include "../../../network/packets/PlayerListPacket.hpp"

Player::Player(
    std::shared_ptr<NetworkPeer> networkPeer, ServerNetworkHandler* networkHandler,
    std::unique_ptr<ConnectionRequest>& connection, const SubClientId subClientId
) : m_NetworkHandler(networkHandler), m_NetworkPeer(std::move(networkPeer)), m_Connection(std::move(connection))
{
    this->m_DisplayName = this->m_Connection->getThirdPartyName();
    this->m_SubClientId = subClientId;
};

void Player::updateSkin(SerializedSkin& skin) {
    this->m_Skin = std::move(skin);
};

void Player::openInventory() {
    ContainerOpenPacket containerOpen;
    containerOpen.targetActorId = 0;
    containerOpen.position = { 0, 0, 0 };
    containerOpen.containerId = 0;
    containerOpen.containerType = ContainerType::INVENTORY;

    this->sendNetworkPacket(containerOpen);
};

void Player::doInitialSpawn() {
    // Start Game
    StartGamePacket startGame;
    startGame.targetActorId = 1;
    startGame.targetRuntimeId = 1;
    startGame.actorGameType = GameType::Default;

    startGame.position = { 0, 0, 0 };
    startGame.rotation = { 0, 0 };

    Nbt::CompoundTag playerData;
    startGame.playerPropertyData = playerData;

    startGame.settings.seed = 1;
    startGame.settings.spawnSettings.type = 0;
    startGame.settings.spawnSettings.userDefinedBiomeName = "plains";
    startGame.settings.spawnSettings.dimension = 0;

    startGame.settings.playerPermissions = CommandPermissionLevel::Internal;
    startGame.settings.baseGameVersion = SharedConstants::CurrentGameVersion.asString();
    startGame.settings.generatorType = GeneratorType::Overworld;
    startGame.settings.gameType = GameType::Creative;
    startGame.settings.newNether = true;
    startGame.settings.difficulty = Difficulty::Normal;
    startGame.settings.isHardcode = false;
    startGame.settings.defaultSpawnBlock = { 0, 0, 0 };

    // 4 chunks (64x64 blocks), 6 chunks (96x96 blocks), 8 chunks (128x128 blocks)
    startGame.settings.serverTickRange = 64 >> 4;

    startGame.settings.editorWorldType = 0;
    startGame.settings.isCreatedInEditor = false;

    startGame.settings.isFromLockedTemplate = false;
    startGame.settings.educationEditionOffer = 0;
    startGame.settings.educationFeatures = false;
    startGame.settings.educationProductId = "";
    startGame.settings.platformLockedContent = false;
    startGame.settings.hasLockedBehaviorPack = false;
    startGame.settings.hasLockedResourcePack = false;
    startGame.settings.createdFromTemplate = false;
    startGame.settings.isTemplateWithLockedSettings = false;
    startGame.settings.overrideForceExperimentalGameplay = false;

    startGame.settings.customSkinsDisabled = false;
    startGame.settings.emoteChatMuted = false;
    startGame.settings.disablePlayerInteractions = false;
    startGame.settings.personaDisabled = false;
    startGame.settings.msaGamertagsOnly = false;
    startGame.settings.chatRestrictionLevel = 0x00;

    startGame.settings.achievementsDisabled = true;
    startGame.settings.bonusChestEnabled = false;
    startGame.settings.startWithMap = false;
    startGame.settings.commandsEnabled = true;
    startGame.settings.dayCycleStopTime = 2000;
    startGame.settings.rainLevel = 2000;
    startGame.settings.lightningLevel = 0;
    startGame.settings.texturepacksRequired = false;

    startGame.settings.experiments.list = {
        {"upcoming_creator_features", true},
        {"gametest", true}
    };
    startGame.settings.experiments.experimentsEverEnabled = false;
    //const auto& gameRules = this->mServerLevel->getGameRules();
    //startGame.settings.gameRules = gameRules.getRules();

    startGame.settings.limitedWorldDepth = 16;
    startGame.settings.limitedWorldWidth = 16;
    startGame.settings.onlySpawnV1Villagers = false;

    startGame.settings.multiplayerEnabled = true;
    startGame.settings.lanBroadcasting = true;
    startGame.settings.xboxBroadcastSettings = 6;
    startGame.settings.platformBroadcastSettings = 6;

    startGame.templateContentIdentity = Util::UUID().toString();
    startGame.isTrial = false;

    startGame.movementSettings.authorityMode = 0;
    startGame.movementSettings.rewindHistorySize = 3200;
    startGame.movementSettings.serverAuthoratativeBlockBreaking = false;

    startGame.currentLevelTime = 0;
    startGame.enchantmentSeed = 1;
    startGame.enableItemStackNetManager = true;
    startGame.serverVersion = "Cubix v" + SharedConstants::CurrentGameVersion.asString();
    startGame.serverBlockTypeRegistryChecksum = 0;
    startGame.worldTemplateId = { 0, 0 };
    startGame.clientSideGeneration = false;
    startGame.blockNetworkIdsAreHashes = true;
    startGame.networkPermissions.serverAuthSoundEnabled = true;

    startGame.multiplayerCorrelationId = this->m_NetworkPeer->getNetworkServer()->m_Identifier.getCorrelationId();

    startGame.levelId = "test";
    startGame.levelName = "Test";

    startGame.settings.serverId = "";
    startGame.settings.worldId = "";
    startGame.settings.scenarioId = "";

    this->sendNetworkPacket(startGame);

    Logger::log(Logger::LogLevel::Info,
        "Player spawned: {}, XUID: {}, Pfid: {}",
            this->getDisplayName(),
            this->m_Connection->getXuid(), this->m_Connection->getPlayFabId());

    if (this->m_SubClientId == SubClientId::PrimaryClient)
    {
        // Item Registry
        ItemRegistryPacket itemRegistry;
        this->sendNetworkPacket(itemRegistry);

        // Creative Content
        CreativeContentPacket creativeContent;
        this->sendNetworkPacket(creativeContent);

        // All available commands
        AvailableCommandsPacket availableCommands;
        this->sendNetworkPacket(availableCommands);
    };

    // Play Status
    PlayStatusPacket playStatus;
    playStatus.status = PlayStatus::PlayerSpawn;

    this->sendNetworkPacket(playStatus);

    // Player list
    /*const auto& clients = this->m_NetworkHandler->getPlayers().at(this->m_NetworkPeer->getNetworkIdentifier());
    const auto& player = clients.at(this->m_SubClientId);

    PlayerListPacket playerList;
    playerList.action = PlayerListPacket::Action::Add;
    playerList.players.emplace_back(player);*/

    //this->m_NetworkHandler->sendPacket(playerList);
};

void Player::disconnect(DisconnectReason reason, bool skipMessage, const std::string& message) const {
    this->m_NetworkHandler->disconnectClient(
        this->m_NetworkPeer->getNetworkIdentifier(),
        this->m_SubClientId,
        reason, skipMessage, message);
};

void Player::sendNetworkPacket(Packet& packet, NetworkPeer::Reliability reliability) const {
    this->m_NetworkPeer->sendPacket(packet, this->m_SubClientId, reliability);
};