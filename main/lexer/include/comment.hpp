#pragma once

#include <vector>
#include <string>

/**
 * @enum eCommentType
 * @brief Enumeration of the different types of comments.
 */
enum class eCommentType
{
	SINGLE_LINE, // Single-line comment type
	MULTI_LINE   // Multi-line comment type
};

/**
 * @struct SComment
 * @brief Structure representing a comment.
 */
struct SComment
{
	eCommentType type;		// The type of the comment
	std::string startDelim; // The starting delimiter of the comment
	std::string endDelim;   // The ending delimiter of the comment
	bool ignore;            // Flag indicating whether to ignore this comment or not
};

/**
 * @class FCommentHandler
 * @brief Class for handling comments in source code.
 */
class FCommentHandler final
{
	std::vector<SComment> m_comments; // List of comments

public:

	/**
	 * @brief Default constructor.
	 */
	FCommentHandler();

	/**
	 * @brief Constructor that initializes the comment handler with a list of comments.
	 * @param comments The list of comments to initialize the handler with.
	 */
	FCommentHandler(const std::vector<SComment>& comments);

	/**
	 * @brief Get the list of comments.
	 * @return The list of comments.
	 */
	std::vector<SComment> GetComments() const;

	/**
	 * @brief Checks if a character is a part of any comment.
	 * @param c The character to check.
	 * @return True if the character is a part of any comment, false otherwise.
	 */
	bool IsComment(const char c) const;

	/**
	 * @brief Checks if a character should be ignored based on comment configuration.
	 * @param c The character to check.
	 * @return True if the character should be ignored, false otherwise.
	 */
	bool ShouldIgnore(const char c) const;
};
