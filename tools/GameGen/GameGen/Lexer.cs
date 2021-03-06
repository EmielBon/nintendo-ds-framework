﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GameGen
{
    class Lexer
    {
        public string[] tokens;
        int tokenIndex = 0;
        string[] presetTokens = { ";", "{", "}", "(", ")", "<", ">", "[", "]", ","};

        public Lexer(string source)
        {
            source = Preprocess(source);
            tokens = source.Trim().Split(' ');
        }

        public string Preprocess(string source)
        {
            var tokens = new List<String>();
            tokens.AddRange(presetTokens);
            tokens.AddRange(Operators.Tokens);

            // Add spaces around preset tokens, so we make sure they are seen as separate tokens
            foreach (var token in tokens)
                source = source.Replace( token, " " + token + " ");
            foreach (var token in tokens)
                if (token.Length == 2)
                    source = source.Replace(token[0] + " " + token[1], token);

            source = Regex.Replace(source, @"\s+", " ");
            
            return source;
        }

        public string PeekToken(int index = 0)
        {
            int i = tokenIndex + index;
            if (i < 0 || i >= tokens.Length)
                return null;
            return tokens[tokenIndex + index];
        }

        public string ReadToken(int index = 0)
        {
            string token = PeekToken(index);
            tokenIndex += index + 1;
            return token;
        }

        public bool MatchToken(string pattern)
        {
            string[] matches = pattern.Split('|');
            string token = PeekToken();
            foreach (string match in matches)
            {
                if (token == match)
                    return true;
            }
            return false;
        }

        public void SkipToken()
        {
            ReadToken();
        }

        public string ReadUntil(string delimiter)
        {
            int startPos = tokenIndex;
            while (tokenIndex < tokens.Length)
            {
                if (PeekToken() == delimiter)
                    break;
                SkipToken();
            }
            
            if (tokenIndex == tokens.Length)
                return null;
            
            return String.Join(" ", tokens.SubArray(startPos, tokenIndex - startPos));
        }

        public string ReadBlock(string openDelimiter, string closeDelimiter)
        {
            int startPos = tokenIndex;
            string open = ReadToken();
            Debug.Assert(open == openDelimiter, "First character in readblock should be delimiter");
            int depth = 1;
            while(depth > 0 && tokenIndex < tokens.Length)
            {
                if (PeekToken() == openDelimiter)
                    depth++;
                if (PeekToken() == closeDelimiter)
                    depth--;
                SkipToken();
            }
            return String.Join(" ", tokens.SubArray(startPos + 1, tokenIndex - startPos - 2));
        }

        public bool HasNext()
        {
            return PeekToken() != null;
        }

        public bool HasNext(int i)
        {
            return PeekToken(i) != null;
        }
    }
}
