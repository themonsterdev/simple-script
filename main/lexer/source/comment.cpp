#include "comment.hpp"

FCommentHandler::FCommentHandler()
	: m_comments(0) // Initialize m_comments with an empty vector
{}

FCommentHandler::FCommentHandler(const std::vector<SComment>& comments)
	: m_comments(comments) // Initialize m_comments with the provided comments vector
{}

std::vector<SComment> FCommentHandler::GetComments() const
{
    return m_comments; // Return the vector of comments
}

bool FCommentHandler::IsComment(const char c) const
{
    // Iterate through all comment types
    for (const auto& comment : m_comments)
    {
        // Check if the character matches the start of a comment
        if (c == comment.startDelim[0])
        {
            // If it matches, return true
            return true;
        }
    }

    // If none of the comment delimiters match the character, return false
    return false;
}

bool FCommentHandler::ShouldIgnore(const char c) const
{
    // Iterate through all comment types
    for (const auto& comment : m_comments)
    {
        // Check if the character matches the start of a comment and if it should be ignored
        if (comment.startDelim[0] == c && comment.ignore)
        {
            // If the character matches the start of a comment and this comment should be ignored, return true
            return true;
        }
    }

    // If no comments to ignore are found, return false
    return false;
}
