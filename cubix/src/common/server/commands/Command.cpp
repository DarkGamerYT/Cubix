#include "Command.hpp"
void Command::run(const CommandOrigin& origin, CommandOutput& output) {
    switch (origin.getType())
    {
        case CommandOriginType::Player: {
            const auto& playerCommandOrigin = dynamic_cast<const PlayerCommandOrigin&>(origin);
            const auto& player = playerCommandOrigin.getPlayer();
            /*if (this->getPermissionLevel() > )
            {
                return;
            };*/

            this->execute(origin, output);
            break;
        };
        default: {
            this->execute(origin, output);
            break;
        };
    }
};

void Command::addFlag(CommandFlag flag) {
    using T = std::underlying_type_t<CommandFlag>;
    this->m_Flags = static_cast<CommandFlag>(
        static_cast<T>(flag) | static_cast<T>(this->m_Flags));
};
bool Command::hasFlag(CommandFlag flag) const {
    using T = std::underlying_type_t<CommandFlag>;
    return (static_cast<T>(this->m_Flags) & static_cast<T>(flag)) != 0;
};